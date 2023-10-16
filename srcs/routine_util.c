/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:35:42 by esali             #+#    #+#             */
/*   Updated: 2023/10/16 12:11:15 by esali            ###   ########.fr       */
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

int	check_is_dead(t_philo *p, t_args *args)
{
	pthread_mutex_lock(&(args->m_dead));
	if (p->args->philo_is_dead)
	{
		pthread_mutex_unlock(&(args->m_dead));
		return (1);
	}
	gettimeofday(&(p->get_time), NULL);
	if (get_ms(p->get_time, p->args) - get_ms(p->last_eat, p->args) > \
	p->args->time_to_die)
	{
		printf("%lu %i died\n", get_ms(p->get_time, p->args), p->nr);
		p->args->philo_is_dead = 1;
		pthread_mutex_unlock(&(args->m_dead));
		return (1);
	}
	pthread_mutex_unlock(&(args->m_dead));
	return (0);
}

void	finish_eat(t_philo *p)
{
	pthread_mutex_lock(&(p->left->m));
	p->left->is_busy = 0;
	pthread_mutex_unlock(&(p->left->m));
	pthread_mutex_lock(&(p->right->m));
	p->right->is_busy = 0;
	pthread_mutex_unlock(&(p->right->m));
	p->nr_eat++;
}

int	check_fork(t_fork *fork)
{
	pthread_mutex_lock(&(fork->m));
	if (!fork->is_busy)
	{
		pthread_mutex_unlock(&(fork->m));
		return (1);
	}
	pthread_mutex_unlock(&(fork->m));
	return (0);
}
