/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:57:45 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/28 17:28:59 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	Print the current status of the philosopher.
	The status includes (in this order):
	[Time in ms since the start of an action]
	[Philosopher's id]
	[Current action (eating, sleeping, ...)]
*/

void	print_status(char *str, t_philo *ph)
{
	long int		time;

	time = -1;
	time = actual_time() - ph->pa->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(ph, 0))
	{
		printf(BOLD"%ld ms "CLEAR, time);
		printf("Philo %d %s", ph->id, str);
	}
}

/*
	Philosopher sleeping and thinking simulation.
	Lock->Sleep->Unlock->Lock->Think->Unlock.
*/

void	sleep_and_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->pa->write_mutex);
	print_status(BLUE"is sleeping\n"CLEAR, ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	ft_usleep(ph->pa->time_to_sleep);
	pthread_mutex_lock(&ph->pa->write_mutex);
	print_status(YELLOW"is thinking\n"CLEAR, ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
}

/*
	Philosopher simulation.
	Take left fork->Take right fork->Eat->Release Forks->Sleep->Think.
*/

/*
	Both forks are taken left first, then right. That is a circular wait on
	paper, and ThreadSanitizer reports the lock-order inversion. It is not
	realised here because thread() staggers the even-numbered philosophers
	by time_to_eat / 10 before they start, so the ring never closes: no
	stall in 27 runs, including 200 philosophers.

	The stagger is therefore load-bearing, not cosmetic. Do not remove it.

	The textbook reorderings were measured and both made things worse, by
	letting one philosopher re-take the same pair while a neighbour starved
	- on 5 800 200 200 7, over ten runs each: ordering the two forks by
	address killed a philosopher in 6, alternating the order by philosopher
	parity in 3, and this left-then-right ordering in none.
*/

void	simulation(t_philo *ph)
{
	if (!ph->right_fork)
	{
		pthread_mutex_lock(&ph->left_fork);
		pthread_mutex_lock(&ph->pa->write_mutex);
		print_status(GREEN"has taken a fork\n"CLEAR, ph);
		pthread_mutex_unlock(&ph->pa->write_mutex);
		ft_usleep(ph->pa->time_to_die * 2);
		pthread_mutex_unlock(&ph->left_fork);
		return ;
	}
	pthread_mutex_lock(&ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(&ph->pa->write_mutex);
	print_status(GREEN"has taken a fork\n"CLEAR, ph);
	print_status(GREEN"has taken a fork\n"CLEAR, ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	pthread_mutex_lock(&ph->pa->write_mutex);
	print_status(PURPLE"is eating\n"CLEAR, ph);
	pthread_mutex_lock(&ph->pa->time_eat_mutex);
	ph->ms_eat = actual_time();
	pthread_mutex_unlock(&ph->pa->time_eat_mutex);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	ft_usleep(ph->pa->time_to_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(&ph->left_fork);
	sleep_and_think(ph);
}
