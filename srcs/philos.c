/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:06:48 by esali             #+#    #+#             */
/*   Updated: 2023/09/07 16:45:20 by esali            ###   ########.fr       */
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

void	*routine(void	*philo)
{
	t_philo			*p;

	p = (t_philo*) philo;
	gettimeofday(&(p->last_eat), NULL);
	while (!(p->args->philo_is_dead))
	{
		pthread_mutex_lock(&(p->left->m));
		p->left->is_busy++;
		gettimeofday(&(p->get_time), NULL);
		printf("%lu %i took left fork\n", get_ms(p->get_time, p->args), p->nr);
		pthread_mutex_lock(&(p->right->m));
		p->right->is_busy++;
		gettimeofday(&(p->get_time), NULL);
		printf("%lu %i took right fork\n",get_ms(p->get_time, p->args), p->nr);
		gettimeofday(&(p->last_eat), NULL);
		printf("%lu %i is eating\n", get_ms(p->last_eat, p->args), p->nr);
		usleep(p->args->time_to_eat * 1000);
		p->left->is_busy = 0;
		p->right->is_busy = 0;
		pthread_mutex_unlock(&(p->right->m));
		pthread_mutex_unlock(&(p->left->m));
		gettimeofday(&(p->get_time), NULL);
		printf("%lu %i is sleeping\n", get_ms(p->get_time, p->args), p->nr);
		usleep(p->args->time_to_sleep * 1000);
		gettimeofday(&(p->get_time), NULL);
		printf("%lu %i is thinking\n", get_ms(p->get_time, p->args), p->nr);
		if (get_ms(p->get_time, p->args) - get_ms(p->last_eat, p->args) > p->args->time_to_die)
		{
			gettimeofday(&(p->get_time), NULL);
			printf("%lu %i died\n", get_ms(p->get_time, p->args), p->nr);
			p->args->philo_is_dead = 1;
			return (NULL);
		}
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
		usleep(100);
		i++;
	}
	i = 0;
	while (i < get_args()->nr_philo)
	{
		if (pthread_join(ps[i]->t, NULL)) //save return value in second argument
			return ;
		i++;
	}
}
