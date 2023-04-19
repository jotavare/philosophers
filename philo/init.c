/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:54:12 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/19 03:31:09 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// assign the stats to the struct
void    assign_stats(t_st *st, char** av)
{
    st->number_of_philos = ft_atoi(av[1]);
    st->time_to_die = ft_atoi(av[2]);
    st->time_to_eat = ft_atoi(av[3]);
    st->time_to_sleep = ft_atoi(av[4]);
    
    if (av[5])
        st->number_of_meals = ft_atoi(av[5]);
}

// assign the stats to the philo struct
void    assign_philo(t_ph *ph, t_st *st)
{
    int i = 0;
    while (i < st->number_of_philos)
    {
        ph[i].id = i + 1;
        ph[i].left_fork = i;
        ph[i].right_fork = i + 1 % st->number_of_philos;
        ph[i].time_left_to_die = st->time_to_die;
        i++;
    }
}
