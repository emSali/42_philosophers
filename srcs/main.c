/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:05:28 by esali             #+#    #+#             */
/*   Updated: 2023/08/28 17:53:44 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void*	print_thread(int i)
{
	printf("\nthis is a thread nr %i", i);
	sleep(2);
	printf("\nEND of %i", i);
	return (NULL);
}

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

int	*init_args(char **argv, int nr)
{
	int	*args;
	int	i;

	i = 1;
	args = (int *)malloc(sizeof(int) * nr);
	if (!args)
		return (NULL);
	while (argv[i])
	{
		args[i - 1] = get_nr(argv[i]);
		if (args[i - 1] < 0)
		{
			printf("\nthe arguments can only contain numeric characters");
			free(args);
			return (NULL);
		}
		i++;
	}
	return (args);
}

int	main(int argc, char **argv)
{
	pthread_t	*t;
	int			*args;
	int			i;

	if (argc < 5 || argc > 6)
		return (0);
	args = init_args(argv, argc);
	if (!args)
		return (1);
	t = (pthread_t *)malloc(sizeof(pthread_t) * args[0]);
	i = 0;
	while(i < args[0])
	{
		if (pthread_create(&t[i], NULL, &print_thread, &i))
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
	return (0);
}
