/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 12:51:09 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/25 16:13:49 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	stop_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->is_alive == false
		|| philo->nb_meals == philo->table->limit_of_meals)
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (false);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->start_lock);
	pthread_mutex_unlock(&philo->table->start_lock);
	if (philo->table->philo_nbr == 1)
		one_philo(philo);
	else
	{
		if (philo->id % 2 == 0)
		{
			print_action(philo, THINK);
			rest(philo->table->time_to_eat / 2, philo);
		}
		while (1)
		{
			if (eating(philo) == false)
				return (NULL);
			if (stop_simulation(philo) == true)
				return (NULL);
			sleeping_thinking(philo);
		}
	}
	return (NULL);
}
