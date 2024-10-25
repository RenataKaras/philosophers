/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end_checks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 17:27:23 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/25 14:51:50 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_full(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->meal_lock);
	if (table->has_meals_counter == true)
	{
		while (i < table->philo_nbr)
		{
			if (table->philos[i].nb_meals == table->limit_of_meals)
			{
				pthread_mutex_unlock(&table->meal_lock);
				return (true);
			}
			i++;
		}
	}
	pthread_mutex_unlock(&table->meal_lock);
	return (false);
}

static bool	philo_died(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->dead_lock);
	pthread_mutex_lock(&table->meal_lock);
	while (i < table->philo_nbr)
	{
		if (table->philos[i].last_meal_time != 0
			&& get_current_time() - table->philos[i].last_meal_time
			> table->time_to_die)
		{
			table->is_alive = false;
			printf("%ld %d died 💀\n",
				get_current_time() - table->start_time, table->philos[i].id);
			pthread_mutex_unlock(&table->meal_lock);
			pthread_mutex_unlock(&table->dead_lock);
			return (true);
		}
		i++;
	}
	pthread_mutex_unlock(&table->meal_lock);
	pthread_mutex_unlock(&table->dead_lock);
	return (false);
}

void	*end_checks(t_table *table)
{
	while (1)
	{
		if (philo_died(table) == true || philo_full(table) == true)
			return (NULL);
		usleep (50);
	}
	return (NULL);
}
