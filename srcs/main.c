/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:05:28 by esali             #+#    #+#             */
/*   Updated: 2023/08/30 15:55:18 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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

int	main(int argc, char **argv)
{
	pthread_t	*t;
	int			*args;
	int			i;
	int*		de_i;

	if (argc < 5 || argc > 6)
		return (0);
	args = init_args(argv, argc);
	if (!args)
		return (1);
	t = (pthread_t *)malloc(sizeof(pthread_t) * args[0]);
	i = 0;
	while(i < args[0])
	{
		de_i = malloc(sizeof(int));
		*de_i = i;
		if (pthread_create(&t[i], NULL, &print_thread, de_i))
			return (1);
		i++;
	}
	i = 0;
	while (i < args[0])
	{
		if (pthread_join(t[i], NULL))
			return (2);
		i++;
	}
	free(args);
	free(t);
	return (0);
}
