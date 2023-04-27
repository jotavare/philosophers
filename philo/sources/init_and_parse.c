/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:22:20 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/26 18:20:19 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_mutex(t_p *p)
{
	pthread_mutex_init(&p->a.write_mutex, NULL);
	pthread_mutex_init(&p->a.dead, NULL);
	pthread_mutex_init(&p->a.time_eat, NULL);
	pthread_mutex_init(&p->a.finish, NULL);
}

int	parse_args(int argc, char **argv, t_p *p)
{
	if ((argc == 5 || argc == 6) && is_number(argv, 0, 1))
	{
		p->a.philos = ft_atoi(argv[1]);
		p->a.time_to_die = ft_atoi(argv[2]);
		p->a.time_to_eat = ft_atoi(argv[3]);
		p->a.time_to_sleep = ft_atoi(argv[4]);
		p->a.meals = -1;
		if (argc == 6)
			p->a.meals = ft_atoi(argv[5]);
		if (p->a.philos <= 0 || p->a.time_to_die <= 0 || p->a.time_to_eat <= 0 \
			|| p->a.time_to_sleep <= 0 || (argc == 6 && p->a.meals <= 0))
			return (0);
		return (1);
	}
	return (0);
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
		p->ph[i].nb_eat = 0;
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
