/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:45:14 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/19 02:58:45 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char** av)
{
    // check the arguments
    check_parser_args(ac);

    // init the stats struct
    t_st *st;
    st = malloc(sizeof(t_st));
    assign_stats(st, av);

    // check if the arguments are valid
    check_args_valid(ac, av, st);

    // init the philo struct
    t_ph *ph;
    ph = malloc(sizeof(t_ph) * st->number_of_philos);
    assign_philo(ph, st);

    // create a thread for each philosopher
    pthread_t *philo;
    philo = malloc(sizeof(pthread_t) * st->number_of_philos);
    int i;

    // init the mutexes and the threads for each philosopher
    i = 0;
    while (i < st->number_of_philos)
    {
        ph[i].st = st;
        pthread_create(&philo[i], NULL, &routine, &ph[i]);
        ft_usleep(100);
        i++;
    }

    // join the threads for each philosopher
    i = 0;
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
