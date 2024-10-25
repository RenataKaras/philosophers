/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 18:16:27 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/25 14:48:33 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int long	get_current_time(void)
{
	struct timeval	time;
	int long		milisec_time;

	if (gettimeofday(&time, NULL) != 0)
		return (write(2, "Time setting error\n", 20), 0);
	milisec_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milisec_time);
}

int long	time_stamp(t_table *table)
{
	long int	current_time;
	long int	new_time;

	current_time = get_current_time();
	new_time = current_time - table->start_time;
	return (new_time);
}

void	print_action(t_philo *philo, int action)
{
	int long	time;

	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->is_alive == true)
	{
		time = time_stamp(philo->table);
		if (action == THINK)
			printf("%ld %d is thinking 🧠\n", time, philo->id);
		if (action == SLEEP)
			printf("%ld %d is sleeping 💤\n", time, philo->id);
		if (action == EAT)
			printf("%ld %d is eating 🍝\n", time, philo->id);
		if (action == FORK)
			printf("%ld %d has taken a fork 🍽️\n", time, philo->id);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
}

void	rest(int long waiting_time, t_philo *philo)
{
	int long	waking_time;

	waking_time = get_current_time() + waiting_time;
	while (waking_time > get_current_time())
	{
		usleep(100);
		pthread_mutex_lock(&philo->table->dead_lock);
		if (philo->table->is_alive == false)
		{
			pthread_mutex_unlock(&philo->table->dead_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->table->dead_lock);
	}
}
