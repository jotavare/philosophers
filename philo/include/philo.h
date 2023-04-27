/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:56:51 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/27 10:21:01 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// libraries
# include <unistd.h>	// write
# include <string.h>	// memset
# include <stdio.h>		// printf 
# include <stdlib.h>	// malloc free
# include <sys/time.h>	// gettimeofday 
# include <sys/types.h>	// usleep
# include <pthread.h>	// pthread
# include <limits.h>	// INT_MAX INT_MIN

// colors
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CLEAR "\033[0m"
# define BOLD "\033[1m"

// structures
typedef struct s_stats
{
	int						philos;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						meals;
	int						number_philos_ate;
	int						stop;
	long int				start_t;
	pthread_mutex_t			write_mutex;
	pthread_mutex_t			dead;
	pthread_mutex_t			time_eat;
	pthread_mutex_t			finish;
}							t_stats;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			left_fork;
	t_stats					*pa;
	long int				ms_eat;
	unsigned int			nb_eat;
	int						finish;
}							t_philo;

typedef struct s_p
{
	t_philo					*ph;
	t_stats					a;
}							t_p;

// simulation.c
void	print_status(char *str, t_philo *ph);
void	sleep_and_think(t_philo *ph);
void	simulation(t_philo *ph);

// check.c
int		check_death(t_philo *ph, int i);
int		check_death2(t_p *p);

// init_and_parse.c
void	init_mutex(t_p *p);
int		parse_args(int argc, char **argv, t_p *p);
int		initialize(t_p *p);

// main.c
void	stop(t_p *p);
int		ft_exit(char *str);

// threads.c
void	*is_dead(void	*data);
void	*thread(void *data);
int		threading(t_p *p);

// time.c
void	ft_usleep(long int time_in_ms);
long	int	actual_time(void);

// utilities.c
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
int		is_number(char **argv, int i, int j);

#endif
