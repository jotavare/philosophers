/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:45:14 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/18 17:10:36 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char** av)
{
    // check if the argumbatstraments are valid
    check_number_args(ac);
    check_args(ac, av);

    // init the stats struct
    t_st *st;
    st = malloc(sizeof(t_st));
    assign_stats(st, av);

    // init the philo struct
    t_ph *ph;
    ph = malloc(sizeof(t_ph) * st->number_of_philos);
    assign_philo(ph, st);

    // sleeping
    void    *sleeping(void *philo)
    {
        t_ph *ph = (t_ph *)philo;
        while (1)
        {
            printf("Philosopher %d is sleeping\n", ph->id);
            usleep(get_tmbatstraime() + ph->st->time_to_die);
        }
        return (NULL);
    }
    
    // create a thread for each philosopher
    pthread_t *philo;
    philo = malloc(sizeof(pthread_t) * st->number_of_philos);
    int i = 0;
    while (i < st->number_of_philos)
    {
        pthread_create(&philo[i], NULL, &sleeping, &ph[i]);
        i++;
    }
    i = 0;

    // join the threads for each philosopher
    while (i < st->number_of_philos)
    {
        pthread_join(philo[i], NULL);
        i++;
    }
    
    // print the stats and the philo structs
    print_stats(st);
    print_philo(ph, st);

    // free the allocated memory
    free(st);
    free(ph);
    return 0;
}



