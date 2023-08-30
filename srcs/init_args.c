/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:05:11 by esali             #+#    #+#             */
/*   Updated: 2023/08/30 15:06:44 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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
