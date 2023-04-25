/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:18:31 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/19 03:18:48 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// sleeping function for each philosopher
void    *sleeping(void *philo)
{
    t_ph *ph = (t_ph *)philo;
    while (1)
    {
        print_status_mutex(ph, "is sleeping...");
    }
    return (NULL);
}

// thinking function for each philosopher
void    *thinking(void *philo)
{
    t_ph *ph = (t_ph *)philo;
    int i = 0;

    while (i < 2)
    {
        print_status_mutex(ph, "is thinking...");
        i++;
    }
    return (NULL);
}

// routine function for each philosopher
void	*routine(void *args)
{
	t_ph		*ph;
    int i = 0;

	ph = (t_ph *)args;
	while (i < 2)
	{
		if (check_death(ph, 0))
			break ;
		if (thinking(ph) == 0)
			continue ;
		if (check_death(ph, 0))
			break ;
        if (sleeping(ph) == 0)
			continue ;
        if (check_death(ph, 0))
			break ;
        i++;
	}
	return (NULL);
}