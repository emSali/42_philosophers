/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:05:11 by esali             #+#    #+#             */
/*   Updated: 2023/09/11 18:31:37 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_nr(char *str)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (-1);
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (ret);
}

int	init_args(char **argv)
{
	t_args	*args;

	args = get_args();
	args->nr_philo = get_nr(argv[1]);
	args->time_to_die = get_nr(argv[2]);
	args->time_to_eat = get_nr(argv[3]);
	args->time_to_sleep = get_nr(argv[4]);
	args->all_ready = args->nr_philo;
	args->philo_is_dead = 0;
	if (argv[5]) {
		args->min_nr_eat = get_nr(argv[5]);
		if (args->min_nr_eat < 1)
			return (1);
	}
	else
		args->min_nr_eat = 0;
	if (args->nr_philo < 1 || args->time_to_die < 1 || args->time_to_eat < 0 || args->time_to_sleep < 0)
	{
			printf("\nthe arguments are not correct");
			return (1);
	}
	return (0);
}

/* Static variables have the property of preserving
their value even after they are out of their scope*/
t_args	*get_args()
{
	static t_args	args;

	return (&args);
}
