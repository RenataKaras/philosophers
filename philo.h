/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 16:46:44 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/25 16:21:36 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

# define THINK 1
# define SLEEP 2
# define EAT 3
# define FORK 4

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	long			nb_meals;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id; //philo is a thread
	t_table			*table;
}					t_philo;

struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			limit_of_meals; //the last optional variable
	long			start_time;
	bool			is_alive; //a philo dies || all philos are full
	bool			has_meals_counter;
	pthread_mutex_t	*forks; //array of forks
	t_philo			*philos; //array of philospphers
	pthread_mutex_t	start_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
};

//utils
int long	get_current_time(void);
int long	time_stamp(t_table *table);
void		print_action(t_philo *philo, int action);
void		rest(int long waiting_time, t_philo *philo);

//input checker
bool		input_checker(int argc, char **argv);
int long	ft_atol(char *str);

//table init
t_table		table_init(char **argv);
bool		forks_init(t_table *table);
bool		philos_init(t_table *table);
int			mutex_init(t_table *table);

//threads
int			philo_thread_creation(t_table *table);
void		join_threads(t_table *table, int index);

//routine
void		*routine(void *arg);

//routine_actions
bool		eating(t_philo *philo);
void		sleeping_thinking(t_philo *philo);
void		one_philo(t_philo *philo);

//end_checks
void		*end_checks(t_table *table);

//cleaner
void		clean(t_table *table);
void		destroy_mutexes(t_table *table);

#endif