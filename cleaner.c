/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaner.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/24 12:08:55 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/24 12:28:48 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	if (table->forks != NULL)
	{
		while (i < table->philo_nbr)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->start_lock);
}

void	clean(t_table *table)
{
	int	i;

	i = 0;
	destroy_mutexes(table);
	if (table->forks != NULL)
		free(table->forks);
	if (table->philos != NULL)
		free(table->philos);
}
