/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:02:33 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/17 19:37:38 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check if the number of arguments is correct
void check_number_args(int ac)
{
    if (ac != 5 && ac != 6)
    {
        printf("Error: Wrong number of arguments\n");
        exit(1);
    }
}

// check if the arguments are valid
void check_args(int ac, char** av)
{
    int i = 1;
    while (i < ac)
    {
        if (ft_atoi(av[i]) <= 0)
        {
            printf("Error: Invalid argument\n");
            exit(1);
        }
        i++;
    }
}

// check if the philosopher is dead
void check_death(t_ph *ph)
{
    if (ph->time_left_to_die <= 0)
    {
        printf("%ld %d died.", get_time(), ph->id);
        exit(1);
    }
}

// check if the philosopher has eaten enough
void check_eat_enough(t_ph *ph)
{
    if (ph->st->nb_of_times_philo_eats != -1)
    {
        if (ph->nb_of_times_philo_eats >= ph->st->nb_of_times_philo_eats)
        {
            printf("%ld %d has eaten enough.", get_time(), ph->id);
            exit(1);
        }
    }
}