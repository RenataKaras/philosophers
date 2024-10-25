/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 16:34:55 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/25 15:06:36 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_table	table;
	int		created_threads;

	if (input_checker(argc, argv) == false)
		write(2, "Wrong input, try again\n", 24);
	table = table_init(argv);
	if (forks_init(&table) == false)
		return (EXIT_FAILURE);
	if (philos_init(&table) == false)
		return (free(table.forks), EXIT_FAILURE);
	created_threads = philo_thread_creation(&table);
	end_checks(&table);
	join_threads(&table, created_threads);
	clean(&table);
	return (EXIT_SUCCESS);
}
