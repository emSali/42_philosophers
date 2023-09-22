/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:06:48 by esali             #+#    #+#             */
/*   Updated: 2023/09/22 18:49:50 by esali            ###   ########.fr       */
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
		return (1);
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

int	p_wait(t_philo *p, t_fork *fork)
{
	while(1)
	{
		usleep(1000);
		if (check_is_dead(p, p->args))
			return (1);
		gettimeofday(&(p->get_time), NULL);
		pthread_mutex_lock(&(fork->m));
		if (!fork->is_busy)
		{
			gettimeofday(&(p->get_time), NULL);
			pthread_mutex_unlock(&(fork->m));
			return (0);
		}
		pthread_mutex_unlock(&(fork->m));
	}
	return (0);
}

int	p_eat(t_philo *p)
{
	if (p->nr % 2 == 0)
	{
		pthread_mutex_lock(&(p->left->m));
		p->left->is_busy++;
		gettimeofday(&(p->get_time), NULL);
		printf("%lu %i has taken a fork\n", get_ms(p->get_time, p->args), p->nr);
		pthread_mutex_lock(&(p->right->m));
		p->right->is_busy++;
		gettimeofday(&(p->get_time), NULL);
		printf("%lu %i has taken a fork\n", get_ms(p->get_time, p->args), p->nr);
		pthread_mutex_unlock(&(p->right->m));
		pthread_mutex_unlock(&(p->left->m));
	}
	else
	{
		pthread_mutex_lock(&(p->right->m));
		p->right->is_busy++;
		gettimeofday(&(p->get_time), NULL);
		printf("%lu %i has taken a fork\n", get_ms(p->get_time, p->args), p->nr);
		pthread_mutex_lock(&(p->left->m));
		p->left->is_busy++;
		gettimeofday(&(p->get_time), NULL);
		printf("%lu %i has taken a fork\n", get_ms(p->get_time, p->args), p->nr);
		pthread_mutex_unlock(&(p->left->m));
		pthread_mutex_unlock(&(p->right->m));
	}
	gettimeofday(&(p->last_eat), NULL);
	printf("%lu %i is eating\n", get_ms(p->last_eat, p->args), p->nr);
	usleep(p->args->time_to_eat * 1000);
	if (p->nr % 2 == 0)
	{
		pthread_mutex_lock(&(p->left->m));
		p->left->is_busy = 0;
		pthread_mutex_lock(&(p->right->m));
		p->right->is_busy = 0;
		pthread_mutex_unlock(&(p->right->m));
		pthread_mutex_unlock(&(p->left->m));
	}
	else
	{
		pthread_mutex_lock(&(p->right->m));
		p->right->is_busy = 0;
		pthread_mutex_lock(&(p->left->m));
		p->left->is_busy = 0;
		pthread_mutex_unlock(&(p->left->m));
		pthread_mutex_unlock(&(p->right->m));
	}
	p->nr_eat++;
	return (0);
}

int	p_sleep(t_philo *p)
{
	int	loop_len;
	int	i;

	i = 0;
	loop_len = p->args->time_to_sleep / 9;
	if (check_is_dead(p, p->args))
		return (1);
	gettimeofday(&(p->get_time), NULL);
	printf("%lu %i is sleeping\n", get_ms(p->get_time, p->args), p->nr);
	if (p->args->time_to_sleep <= 10)
	{
		usleep(p->args->time_to_sleep * 1000);
		return (0);
	}
	while(i < loop_len)
	{
		if (check_is_dead(p, p->args))
			return (1);
		usleep(9000);
		i++;
	}
	usleep((p->args->time_to_sleep % 9) * 1000);
	return (0);
}

void	*routine(void	*philo)
{
	t_philo			*p;

	p = (t_philo *) philo;
	gettimeofday(&(p->last_eat), NULL);
	if (p->nr % 2)
		usleep(1000 * 50);
	while (!check_is_dead(p, p->args))
	{
		if (p->args->min_nr_eat && p->nr_eat >= p->args->min_nr_eat)
			return (NULL);
		if (p->nr % 2 == 0)
		{
			if (p_wait(p, p->left))
				return (NULL);
		}
		else
		{
			if (p_wait(p, p->right))
				return (NULL);
		}
		if (p_eat(p))
			return (NULL);
		if (p_sleep(p))
			return (NULL);
		gettimeofday(&(p->get_time), NULL);
		if (p->args->philo_is_dead)
			return (NULL);
		printf("%lu %i is thinking\n", get_ms(p->get_time, p->args), p->nr);
	}
	return (NULL);
}

//usleep(100);
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
