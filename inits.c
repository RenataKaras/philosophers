/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inits.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:19:40 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/25 14:27:19 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	forks_init(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(table->philo_nbr * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (write(2, "Memory allocation error\n", 25), false);
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&table->forks[i]);
				write(2, "Error creating fork mutexes\n", 29);
				i--;
			}
			free(table->forks);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	philos_init(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(table->philo_nbr * sizeof(t_philo));
	if (!table->philos)
		return (write(2, "Memory allocation error\n", 25), false);
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].nb_meals = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].right_fork = &table->forks[i];
		if (table->philos[i].id == table->philo_nbr)
			table->philos[i].left_fork = &table->forks[0];
		else
			table->philos[i].left_fork = &table->forks[i + 1];
		table->philos[i].table = table;
		i++;
	}
	return (true);
}

int	mutex_init(t_table *table)
{
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
		return (write(2, "Mutex init error\n", 18), 1);
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->meal_lock);
		return (write(2, "Mutex init error\n", 18), 1);
	}
	if (pthread_mutex_init(&table->start_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->meal_lock);
		pthread_mutex_destroy(&table->dead_lock);
		return (write(2, "Mutex init error\n", 18), 1);
	}
	return (0);
}

t_table	table_init(char **argv)
{
	t_table	table;

	table.start_time = 0;
	table.is_alive = true;
	table.philo_nbr = ft_atol(argv[1]);
	table.time_to_die = ft_atol(argv[2]);
	table.time_to_eat = ft_atol(argv[3]);
	table.time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
	{
		table.has_meals_counter = true;
		table.limit_of_meals = ft_atol(argv[5]);
	}
	else
	{
		table.has_meals_counter = false;
		table.limit_of_meals = -1;
	}
	mutex_init(&table);
	table.philos = NULL;
	return (table);
}
