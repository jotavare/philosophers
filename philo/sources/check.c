/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:57:51 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/28 17:38:58 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	Checks if the philosopher has died due to starvation, and
	if so, prints a message indicating that the philosopher has died.
*/

int	check_death(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->pa->dead_mutex);
	if (i)
		ph->pa->stop = i;
	if (ph->pa->stop)
	{
		pthread_mutex_unlock(&ph->pa->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->pa->dead_mutex);
	return (0);
}

/*
	Checks if the philosopher has eaten the required amount of times.
*/

/*
	Blocks until every detached death-monitor thread has returned. They
	dereference the philosopher array, so freeing it while one is still
	sleeping is a use-after-free.
*/

static void	wait_monitors(t_p *p)
{
	int	live;

	live = 1;
	while (live)
	{
		pthread_mutex_lock(&p->a.dead_mutex);
		live = p->a.monitors;
		pthread_mutex_unlock(&p->a.dead_mutex);
		if (live)
			ft_usleep(1);
	}
}

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
	wait_monitors(p);
	pthread_mutex_lock(&p->a.dead_mutex);
	i = (p->a.stop == 2);
	pthread_mutex_unlock(&p->a.dead_mutex);
	if (i)
		printf(GREEN"Each philosopher ate %d time(s)\n"CLEAR, p->a.meals);
	free(p->ph);
}

/*
	Prints custom error message.
*/

int	ft_exit(char *str)
{
	printf(RED"Error : "CLEAR);
	printf(RED"%s"CLEAR, str);
	printf(RED"./philo [Philos] [Die] [Eat] [Sleep] [Meals]\n"CLEAR);
	return (0);
}
