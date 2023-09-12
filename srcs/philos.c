/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:06:48 by esali             #+#    #+#             */
/*   Updated: 2023/09/12 15:06:20 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_ms(struct timeval time, t_args *args)
{
	long	start_time;
	long	new_time;

	start_time = args->start.tv_sec * 1000 + args->start.tv_usec / 1000;
	new_time = time.tv_sec * 1000 + time.tv_usec / 1000 - start_time;
	return (new_time);
}

int	p_wait(t_philo *p, t_fork *fork)
{
	while(fork->is_busy)
	{
		if (p->args->philo_is_dead)
			return (0);
		gettimeofday(&(p->get_time), NULL);
		if (get_ms(p->get_time, p->args) - get_ms(p->last_eat, p->args) > p->args->time_to_die)
		{
			printf("%lu %i died\n", get_ms(p->get_time, p->args), p->nr);
			p->args->philo_is_dead = 1;
			return (1);
		}
	}
	return (0);
}

int	p_eat(t_philo *p)
{
	pthread_mutex_lock(&(p->left->m));
	p->left->is_busy++;
	gettimeofday(&(p->get_time), NULL);
	if (p->args->philo_is_dead)
		return (1);
	printf("%lu %i has taken a fork\n", get_ms(p->get_time, p->args), p->nr);
	if (p_wait(p, p->right))
		return (1);
	pthread_mutex_lock(&(p->right->m));
	p->right->is_busy++;
	gettimeofday(&(p->get_time), NULL);
	if (p->args->philo_is_dead)
		return (1);
	printf("%lu %i has taken a fork\n",get_ms(p->get_time, p->args), p->nr);
	gettimeofday(&(p->last_eat), NULL);
	if (p->args->philo_is_dead)
		return (1);
	printf("%lu %i is eating\n", get_ms(p->last_eat, p->args), p->nr);
	usleep(p->args->time_to_eat * 1000);
	pthread_mutex_unlock(&(p->right->m));
	pthread_mutex_unlock(&(p->left->m));
	p->left->is_busy = 0;
	p->right->is_busy = 0;
	p->nr_eat++;
	return (0);
}

void	*routine(void	*philo)
{
	t_philo			*p;

	p = (t_philo*) philo;
	gettimeofday(&(p->last_eat), NULL);
	while (!(p->args->philo_is_dead))
	{
		if (p->args->min_nr_eat && p->nr_eat >= p->args->min_nr_eat)
			return (NULL);
		if (p_wait(p, p->left))
			return (NULL);
		if (p_eat(p))
			return (NULL);
		gettimeofday(&(p->get_time), NULL);
		if (p->args->philo_is_dead)
			return (NULL);
		printf("%lu %i is sleeping\n", get_ms(p->get_time, p->args), p->nr);
		usleep(p->args->time_to_sleep * 1000);
		gettimeofday(&(p->get_time), NULL);
		if (p->args->philo_is_dead)
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
		//usleep(100);
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
