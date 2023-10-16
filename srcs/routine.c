/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:06:48 by esali             #+#    #+#             */
/*   Updated: 2023/10/16 12:08:52 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	p_wait(t_philo *p, int nr)
{
	while (1)
	{
		if (check_is_dead(p, p->args))
			return (1);
		if (nr % 2 == 0)
		{
			if (p->args->nr_philo == 0)
				continue ;
			if (check_fork(p->left))
				return (0);
		}
		else
		{
			if (check_fork(p->right))
				return (0);
		}
		usleep(100);
	}
	return (0);
}

int	p_eat(t_philo *p)
{
	pthread_mutex_lock(&(p->left->m));
	p->left->is_busy = 1;
	pthread_mutex_unlock(&(p->left->m));
	if (check_is_dead(p, p->args))
		return (1);
	gettimeofday(&(p->get_time), NULL);
	printf("%lu %i has taken left fork\n", get_ms(p->get_time, p->args), p->nr);
	if (p_wait(p, 1))
		return (1);
	pthread_mutex_lock(&(p->right->m));
	p->right->is_busy++;
	pthread_mutex_unlock(&(p->right->m));
	gettimeofday(&(p->get_time), NULL);
	printf("%lu %i has taken right fork\n", get_ms(p->get_time, p->args), p->nr);
	if (check_is_dead(p, p->args))
		return (1);
	gettimeofday(&(p->last_eat), NULL);
	printf("%lu %i is eating\n", get_ms(p->last_eat, p->args), p->nr);
	usleep(p->args->time_to_eat * 1000);
	finish_eat(p);
	return (0);
}

int	p_sleep(t_philo *p)
{
	int	loop_len;
	int	i;

	if (check_is_dead(p, p->args))
		return (1);
	gettimeofday(&(p->get_time), NULL);
	printf("%lu %i is sleeping\n", get_ms(p->get_time, p->args), p->nr);
	loop_len = p->args->time_to_sleep / 9;
	i = 0;
	while (i < loop_len)
	{
		gettimeofday(&(p->get_time), NULL);
		if (get_ms(p->get_time, p->args) - get_ms(p->last_eat, p->args) > \
		p->args->time_to_die)
		{
			check_is_dead(p, p->args);
			return (1);
		}
		usleep(9000);
		i++;
	}
	return (0);
}

void	*routine(void	*philo)
{
	t_philo			*p;

	p = (t_philo *) philo;
	gettimeofday(&(p->last_eat), NULL);
	if (p->nr % 2 == 0)
		usleep(1000 * 50);
	while (!check_is_dead(p, p->args))
	{
		if (p->args->min_nr_eat && p->nr_eat >= p->args->min_nr_eat)
			return (NULL);
		if (p_wait(p, 2))
			return (NULL);
		if (p_eat(p))
			return (NULL);
		if (p_sleep(p))
			return (NULL);
		gettimeofday(&(p->get_time), NULL);
		if (check_is_dead(p, p->args))
			return (NULL);
		printf("%lu %i is thinking\n", get_ms(p->get_time, p->args), p->nr);
	}
	return (NULL);
}

void	start_philos(t_philo **ps, t_args *args)
{
	int		i;

	i = 0;
	gettimeofday(&(args->start), NULL);
	while (i < args->nr_philo)
	{
		if (pthread_create(&(ps[i]->t), NULL, &routine, (void *) ps[i]))
			return ;
		i++;
	}
	i = 0;
	while (i < get_args()->nr_philo)
	{
		if (pthread_join(ps[i]->t, NULL))
			return ;
		i++;
	}
}
