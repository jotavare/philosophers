/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:36:23 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/17 19:37:40 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// get the time
long get_time(void)
{
    struct timeval  tv;
    long            ms;

    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
    return (ms);
}

// libft functions
long	ft_atoi(const char *str)
{
	long	i;
	long	number;
	int		sign;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

// print the stats struct
void print_stats(t_st *st)
{
    printf("\nNumber of philosophers: %d\n", st->number_of_philos);
    printf("Time to die: %d\n", st->time_to_die);
    printf("Time to eat: %d\n", st->time_to_eat);
    printf("Time to sleep: %d\n", st->time_to_sleep);
    if (st->nb_of_times_philo_eats)
        printf("Number of times each philosopher must eat: %d\n", st->nb_of_times_philo_eats);
}

// print the philo struct
void print_philo(t_ph *ph, t_st *st)
{
    int i = 0;
    while (i < st->number_of_philos)
    {
        printf("\n%ld Philosopher %d\n", get_time() ,ph[i].id);
		printf("Left fork: %d\n", ph[i].left_fork);
		printf("Right fork: %d\n", ph[i].right_fork);
        printf("Time left to die: %d\n", ph[i].time_left_to_die);
        i++;
    }
}
