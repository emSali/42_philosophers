/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:05:28 by esali             #+#    #+#             */
/*   Updated: 2023/09/04 12:47:00 by esali            ###   ########.fr       */
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







void*	print_thread(void *i)
{
	int	index;

	index = *(int*) i;
	printf("\nthis is a thread nr %i", index);
	sleep(2);
	printf("\nEND of %i", index);
	free(i);
	return (NULL);
}

void	create_threads(int *args)
{
	pthread_t	*t;
	int			i;
	int*		de_i;

	t = (pthread_t *)malloc(sizeof(pthread_t) * args[0]);
	i = 0;
	while(i < args[0])
	{
		de_i = malloc(sizeof(int));
		*de_i = i;
		if (pthread_create(&t[i], NULL, &print_thread, de_i))
			printf("\nFailed to create thread");
		i++;
	}
	i = 0;
	while (i < args[0])
	{
		if (pthread_join(t[i], NULL))
			printf("\nFailed to join thread");
		i++;
	}
	free(t);
}


