/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:22:20 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/28 17:29:36 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_mutex(t_p *p)
{
	pthread_mutex_init(&p->a.write_mutex, NULL);
	pthread_mutex_init(&p->a.dead_mutex, NULL);
	pthread_mutex_init(&p->a.time_eat_mutex, NULL);
	pthread_mutex_init(&p->a.finish_mutex, NULL);
}

int	initialize(t_p *p)
{
	int	i;

	i = 0;
	p->a.start_t = actual_time();
	p->a.stop = 0;
	p->a.number_philos_ate = 0;
	init_mutex(p);
	while (i < p->a.philos)
	{
		p->ph[i].id = i + 1;
		p->ph[i].ms_eat = p->a.start_t;
		p->ph[i].nb_philo_ate = 0;
		p->ph[i].finish = 0;
		p->ph[i].right_fork = NULL;
		pthread_mutex_init(&p->ph[i].left_fork, NULL);
		if (p->a.philos == 1)
			return (1);
		if (i == p->a.philos - 1)
			p->ph[i].right_fork = &p->ph[0].left_fork;
		else
			p->ph[i].right_fork = &p->ph[i + 1].left_fork;
		i++;
	}
	return (1);
}
