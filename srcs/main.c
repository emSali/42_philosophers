/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:05:28 by esali             #+#    #+#             */
/*   Updated: 2023/09/03 17:33:20 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Too many arguments\n");
		return (1);
	}
	if (init_args(argv))
		return (1);
	init_philos(get_args()->nr_philo);
	init_threads();
	free_philos(get_args()->nr_philo);
	return (0);
}
