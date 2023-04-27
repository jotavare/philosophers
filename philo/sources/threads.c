/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:22:35 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/27 12:37:13 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	Checks whether a philosopher has died due to starvation, and
	if so, prints a message indicating that the philosopher has died.
*/

void	*is_dead(void	*data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	ft_usleep(ph->pa->time_to_die);
	pthread_mutex_lock(&ph->pa->time_eat);
	pthread_mutex_lock(&ph->pa->finish);
	if (!check_death(ph, 0) && !ph->finish && ((actual_time() - ph->ms_eat) \
		>= (long)(ph->pa->time_to_die)))
	{
		pthread_mutex_unlock(&ph->pa->time_eat);
		pthread_mutex_unlock(&ph->pa->finish);
		pthread_mutex_lock(&ph->pa->write_mutex);
		print_status(RED"died\n"CLEAR, ph);
		pthread_mutex_unlock(&ph->pa->write_mutex);
		check_death(ph, 1);
	}
	pthread_mutex_unlock(&ph->pa->time_eat);
	pthread_mutex_unlock(&ph->pa->finish);
	return (NULL);
}

/*
	thread: This function is a thread function that simulates the behavior of a philosopher.
	It creates a new thread to check whether the philosopher has died, and then performs the philosopher's actions.
	Keeps track of how many times the philosopher has eaten.
*/

void	*thread(void *data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->pa->time_to_eat / 10);
	while (!check_death(ph, 0))
	{
		pthread_create(&ph->thread_death_id, NULL, is_dead, data);
		simulation(ph);
		if ((int)++ph->nb_eat == ph->pa->meals)
		{
			pthread_mutex_lock(&ph->pa->finish);
			ph->finish = 1;
			ph->pa->number_philos_ate++;
			if (ph->pa->number_philos_ate == ph->pa->philos)
			{
				pthread_mutex_unlock(&ph->pa->finish);
				check_death(ph, 2);
			}
			pthread_mutex_unlock(&ph->pa->finish);
			return (NULL);
		}
		
	}
	pthread_join(ph->thread_death_id, NULL);
	return (NULL);
}

/*
	Creates a thread for each philosopher.
*/

int	threading(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->a.philos)
	{
		p->ph[i].pa = &p->a;
		if (pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]) != 0)
			return (ft_exit("Pthread did not return 0\n"));
		i++;
	}
	return (1);
}
