/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 15:25:08 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/25 15:06:45 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_number(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int long	ft_atol(char *str)
{
	int			i;
	int long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result = result + (str[i] - '0');
		i++;
	}
	return (result);
}

static bool	number_validation(char **argv)
{
	int	i;

	if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
		return (false);
	i = 2;
	while (argv[i])
	{
		if (ft_atol(argv[i]) < 1 || ft_atol(argv[i]) > INT_MAX)
			return (false);
		i++;
	}
	return (true);
}

bool	input_checker(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (false);
	if (is_number(argv) == false)
		return (false);
	if (number_validation(argv) == false)
		return (false);
	return (true);
}
