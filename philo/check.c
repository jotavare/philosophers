/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:02:33 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/16 04:27:51 by jotavare         ###   ########.fr       */
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

// print the stats struct
void print_stats(t_st *stats)
{
    printf("\nNumber of philosophers: %d\n", stats->number_of_philos);
    printf("Time to die: %d\n", stats->time_to_die);
    printf("Time to eat: %d\n", stats->time_to_eat);
    printf("Time to sleep: %d\n", stats->time_to_sleep);
    if (stats->nb_of_times_philo_eats)
        printf("Number of times each philosopher must eat: %d\n", stats->nb_of_times_philo_eats);
}

// print the philo struct
void print_philo(t_ph *philo, t_st *stats)
{
    int i = 0;
    while (i < stats->number_of_philos)
    {
        printf("\nPhilosopher %d\n", philo[i].id);
        printf("Left fork: %d\n", philo[i].left_fork);
        printf("Right fork: %d\n", philo[i].right_fork);
        printf("Time left to die: %d\n", philo[i].time_left_to_die);
        i++;
    }
}

// assign the stats to the struct
void assign_stats(t_st *st, char** av)
{
    stats->number_of_philos = ft_atoi(av[1]);
    stats->time_to_die = ft_atoi(av[2]);
    stats->time_to_eat = ft_atoi(av[3]);
    stats->time_to_sleep = ft_atoi(av[4]);
    
    if (av[5])
        stats->nb_of_times_philo_eats = ft_atoi(av[5]);
}

// assign the stats to the philo struct
void assign_philo(t_ph *philo, t_st *stats)
{
    int i = 0;
    while (i < stats->number_of_philos)
    {
        philo[i].id = i + 1;
        philo[i].left_fork = i;
        philo[i].right_fork = (i + 1) % stats->number_of_philos;
        philo[i].time_left_to_die = stats->time_to_die;
        i++;
    }
}