/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:44:39 by esali             #+#    #+#             */
/*   Updated: 2023/09/12 15:13:02 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*new_philo(int number, t_args *args, t_fork *left, t_fork *right)
{
	t_philo	*new_philo;

	new_philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->nr_eat = 0;
	new_philo->nr = number + 1;
	new_philo->args = args;
	new_philo->left = left;
	new_philo->right = right;
	return (new_philo);
}

t_fork	*new_fork(void)
{
	t_fork	*new_fork;

	new_fork = (t_fork *)malloc(sizeof(t_fork));
	if (!new_fork)
		return (NULL);
	pthread_mutex_init(&(new_fork->m), NULL);
	new_fork->is_busy = 0;
	return (new_fork);
}

t_philo	**init_philos(t_args *args)
{
	t_philo	**ps;
	t_fork	*first_left;
	t_fork	*left;
	t_fork	*right;
	int		i;

	ps = (t_philo **)malloc(sizeof(t_philo) * args->nr_philo);
	if (!ps)
		return (NULL);
	i = 0;
	right = new_fork();
	first_left = right;
	while (i < (args->nr_philo - 1))
	{
		left = right;
		right = new_fork();
		ps[i] = new_philo(i, args, left, right);
		i++;
	}
	ps[i] = new_philo(i, args, right, first_left);
	return (ps);
}

void	free_philos(t_philo **ps)
{
	t_args	*args;
	int		i;

	i = 0;
	args = get_args();
	pthread_mutex_destroy(&(args->m));
	while (i < args->nr_philo)
	{
		pthread_mutex_destroy(&(ps[i]->left->m));
		free(ps[i]->left);
		free(ps[i]);
		i++;
	}
	free(ps);
}
