/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:36:23 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/25 18:44:46 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(char *str)
{
	printf("Error : ");
	printf("%s", str);
	return (0);
}

long	actual_time(void)
{
	long			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_exit("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
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
    if (st->number_of_meals)
        printf("Number of times each philosopher must eat: %d\n", st->number_of_meals);
}

// print the philo struct
void print_philo(t_ph *ph, t_st *st)
{
    int i = 0;
    while (i < st->number_of_philos)
    {
        printf("\n%ld Philosopher %d\n", actual_time() ,ph[i].id);
		printf("Left fork: %d\n", ph[i].left_fork);
		printf("Right fork: %d\n", ph[i].right_fork);
        printf("Time left to die: %d\n", ph[i].time_left_to_die);
        i++;
    }
}

//  print the status of the philosopher with a mutex
void    print_status_mutex(t_ph *ph, char *status)
{
    pthread_mutex_lock(&ph->st->print_status);
    printf("%ld Philosopher %d %s \n", actual_time(), ph->id, status);
    pthread_mutex_unlock(&ph->st->print_status);
}