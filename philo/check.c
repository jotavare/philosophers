/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:02:33 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/19 02:40:01 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check if the number of arguments is correct
void check_parser_args(int ac)
{
    if (ac != 5 && ac != 6)
    {
        printf("Error: Wrong number of arguments.\n");
        printf("./philo [Philos] [Die] [Eat] [Sleep] [Meals]\n");
        exit(1);
    }
}

// check if the arguments are valid
void check_args_valid(int ac, char** av, t_st *st)
{
    st->number_of_philos = ft_atoi(av[1]);
    st->time_to_die = ft_atoi(av[2]);
    st->time_to_eat = ft_atoi(av[3]);
    st->time_to_sleep = ft_atoi(av[4]);
    if(av[5])
        st->number_of_meals = ft_atoi(av[5]);
    else
        st->number_of_meals = -1;
    if(st->number_of_philos < 2
        || st->time_to_die < 0
        || st->time_to_eat < 0
        || st->time_to_sleep < 0
        || (ac == 6 && st->number_of_meals < 1))
    {
        printf("Error: Invalid argument.\n");
        printf("./philo [Philos >= 2] [Die >= 0] [Eat >= 0] [Sleep >= 0] [Meals >= 1]\n");
        exit(1);
    }
}

// check if the philosopher is dead
int	check_death(t_ph *ph, int i)
{
	pthread_mutex_lock(&ph->st->dead);
	if (i)
		ph->st->stop = i;
	if (ph->st->stop)
	{
		pthread_mutex_unlock(&ph->st->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->st->dead);
	return (0);
}

// check if the philosopher has eaten enough
void check_eat_enough(t_ph *ph)
{
    if (ph->st->number_of_meals != -1)
    {
        if (ph->eat_cout >= ph->st->number_of_meals)
        {
            printf("%ld %d has eaten enough.", actual_time(), ph->id);
            exit(1);
        }
    }
}