/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:41:00 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/19 03:07:49 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// libraries
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

// struct for each philosopher.
typedef struct s_ph
{
    struct s_st *st;
    int id;
    int eat_cout;
    int status;
    int eating;
    int time_left_to_die;
    int left_fork;
    int right_fork;
    pthread_mutex_t lock;
}   t_ph;

// struct for necessary stats.
typedef struct s_st
{
    int number_of_philos;
    int number_of_meals;
    int finished;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int time_to_start;
    int stop;
    pthread_mutex_t dead;
    pthread_mutex_t print_status;
    pthread_mutex_t lock;
    pthread_mutex_t *forks;
}   t_st;

//  stats and philo structs
typedef struct s_both
{
    t_st    *st;
    t_ph    *ph;
}   t_both;

// utility functions
long    ft_atoi(const char *str);

long int	actual_time(void);
void	ft_usleep(long int time_in_ms);

// check functions
int     check_death(t_ph *ph, int i);
void    check_parser_args(int ac);
void    check_args_valid(int ac, char** av, t_st *st);
void    check_eat_enough(t_ph *ph);
void    print_stats(t_st *st);
void    print_philo(t_ph *ph, t_st *st);
void	*routine(void *args);
void    eat(t_ph *ph);

int ft_exit(char *str);

// init functions
void    assign_stats(t_st *st, char** av);
void    assign_philo(t_ph *ph, t_st *st);

// actions functions
void    *sleeping(void *philo);
void    print_status_mutex(t_ph *ph, char *status);

#endif