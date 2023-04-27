/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:57:51 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/27 13:05:40 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	Checks if the philosopher has died due to starvation, and
	if so, prints a message indicating that the philosopher has died.
*/

int	check_death(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->pa->dead);
	if (i)
		ph->pa->stop = i;
	if (ph->pa->stop)
	{
		pthread_mutex_unlock(&ph->pa->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->pa->dead);
	return (0);
}

int	check_death2(t_p *p)
{
	pthread_mutex_lock(&p->a.dead);
	if (p->a.stop)
	{
		pthread_mutex_unlock(&p->a.dead);
		return (1);
	}
	pthread_mutex_unlock(&p->a.dead);
	return (0);
}

/*
	Checks if the philosopher has eaten the required amount of times.
*/

void	stop(t_p *p)
{
	int	i;

	i = -1;
	while (!check_death(p->ph, 0))
		ft_usleep(1);
	while (++i < p->a.philos)
	{
		pthread_join(p->ph[i].thread_id, NULL);
	}
	pthread_mutex_destroy(&p->a.write_mutex);
	i = -1;
	while (++i < p->a.philos)
	{
		pthread_mutex_destroy(&p->ph[i].left_fork);
		
	}
	if (p->a.stop == 2)
		printf(GREEN"Each philosopher ate %d time(s)\n"CLEAR, p->a.meals);
	free(p->ph);
}

/*
	free(p.ph);
	Prints custom error message.
*/

int	ft_exit(char *str)
{
	printf(RED"Error : "CLEAR);
	printf(RED"%s"CLEAR, str);
	printf(RED"./philo [Philos] [Die] [Eat] [Sleep] [Meals]\n"CLEAR);
	return (0);
}