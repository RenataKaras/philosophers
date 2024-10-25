/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 16:43:58 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/25 16:03:21 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_thread_creation(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->start_lock);
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL,
				&routine, &table->philos[i]) != 0)
		{
			pthread_mutex_unlock(&table->start_lock);
			return (write(2, "Creating philo thread error\n", 29), i);
		}
		i++;
	}
	table->start_time = get_current_time();
	pthread_mutex_unlock(&table->start_lock);
	return (i);
}
//join threads here if the creation fails

void	join_threads(t_table *table, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
		{
			write (2, "Joining philo thread error\n", 28);
			return ;
		}
		i++;
	}
}
