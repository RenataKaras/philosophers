/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_actions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 16:25:25 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/25 16:20:11 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping_thinking(t_philo *philo)
{
	int long	thinking_time;

	thinking_time = 2 * philo->table->time_to_eat - philo->table->time_to_sleep;
	if (thinking_time < 0)
		thinking_time = 0;
	print_action(philo, SLEEP);
	rest(philo->table->time_to_sleep, philo);
	print_action(philo, THINK);
	if (philo->table->philo_nbr % 2 != 0)
		rest(thinking_time, philo);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->table->meal_lock);
	pthread_mutex_unlock(philo->right_fork);
	rest(philo->table->time_to_die, philo);
}

static bool	second_fork_pickup(t_philo *philo, pthread_mutex_t *second_fork)
{
	if (pthread_mutex_lock(second_fork) == 0)
	{
		print_action(philo, FORK);
		print_action(philo, EAT);
		pthread_mutex_lock(&philo->table->meal_lock);
		philo->last_meal_time = get_current_time();
		philo->nb_meals += 1;
		pthread_mutex_unlock(&philo->table->meal_lock);
		rest(philo->table->time_to_eat, philo);
		pthread_mutex_unlock(second_fork);
		return (true);
	}
	else
		return (write(2, "Fork locking error\n", 20), false);
}

static bool	first_fork_pickup(t_philo *philo, pthread_mutex_t *first_fork,
	pthread_mutex_t *second_fork)
{
	if (pthread_mutex_lock(first_fork) == 0)
	{
		print_action(philo, FORK);
		if (second_fork_pickup(philo, second_fork) == false)
			return (false);
		pthread_mutex_unlock(first_fork);
		return (true);
	}
	else
		return (write(2, "Fork locking error\n", 20), false);
}

bool	eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (first_fork_pickup(philo, first_fork, second_fork) == false)
		return (false);
	return (true);
}
