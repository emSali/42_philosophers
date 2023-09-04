/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:01:13 by esali             #+#    #+#             */
/*   Updated: 2023/09/04 18:27:09 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_philo	**philos;
	t_args	*args;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong amount of arguments\n");
		return (1);
	}
	if (init_args(argv))
		return (1);
	args = get_args();
	philos = init_philos(args);
	start_philos(philos, args);
	free_philos(philos);
	return (0);
}
