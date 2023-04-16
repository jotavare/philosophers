/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:45:14 by jotavare          #+#    #+#             */
/*   Updated: 2023/04/16 04:29:10 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char** av)
{
    check_number_args(ac);
    check_args(ac, av);

    t_stats *stats;
    stats = malloc(sizeof(t_stats));
    void assign_stats(t_stats *stats, char** av)
    
    t_philo *philo;
    philo = malloc(sizeof(t_philo) * stats->number_of_philos);
    void assign_philo(t_philo *philo, t_stats *stats)

    /*
    // create a thread for each philosopher
    pthread_t philosopher[stats->number_of_philos];
    int j = 0;
    while (j < stats->number_of_philos)
    {
        pthread_create(&philosopher[j], NULL, &eat_sleep_think, NULL);
        j++;
        printf("Philosopher %d is alive\n", j);
    }

    while (j < stats->number_of_philos)
    {
        pthread_join(philosopher[j], NULL);
        j++;
        printf("Philosopher %d joined\n", j);
    }*/

    print_stats(stats);
    print_philo(philo, stats);

    free(stats);
    free(philo);
    return 0;
}