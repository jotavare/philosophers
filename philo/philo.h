/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:41:00 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/16 03:58:11 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

// struct for each philosopher.
typedef struct s_ph
{
    int id;
    int left_fork;
    int right_fork;
    int time_left_to_die;
}   t_ph;

// struct for necessary stats.
typedef struct s_st
{
    int number_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_of_times_philo_eats;
}   t_st;

// utility functions
long    get_time(void);
long    ft_atoi(const char *str);

// check functions
void    check_number_args(int ac);
void    check_args(int ac, char** av);
void    print_stats(t_st *stats);
void    print_philo(t_ph *philo, t_st *stats);

#endif
