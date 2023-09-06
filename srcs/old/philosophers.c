/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:07:44 by esali             #+#    #+#             */
/*   Updated: 2023/09/06 18:24:38 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_ms(struct timeval time, t_args *args)
{
	long	start_time;
	long	new_time;

	start_time = args->start.tv_sec * 1000 + args->start.tv_usec / 1000;
	new_time = time.tv_sec * 1000 + time.tv_usec / 1000 - start_time;
	return (new_time);
}

int	wait_for_fork(t_philo *p, t_args *args)
{
	int		i;

	i = 0;
	while(p->prv->is_eating || p->nxt->is_eating || i == 0)
	{
		if (args->philo_is_dead)
		return (1);
		gettimeofday(&(p->get_time), NULL);
		if ((get_ms(p->get_time, args) - get_ms(p->last_eat, args)) > args->time_to_die \
		&& (args->min_nr_eat == 0 || p->nr_eat < args->min_nr_eat))
		{
			args->philo_is_dead = 1;
			printf("%lu %i died\n", get_ms(p->get_time, args), p->nr);
			return (1);
		}
		usleep(1);
		i = 1;
	}
	if (args->philo_is_dead)
		return (1);
	return (0);
}

int	eat_sleep_think(t_philo *p, t_args *args)
{
	if (args->philo_is_dead)
		return (1);
	pthread_mutex_lock(&(p->m));
	if (!(p->prv->is_eating) && !(p->nxt->is_eating))
	{
		p->is_eating = 1;
		pthread_mutex_unlock(&(p->m));
		gettimeofday(&(p->last_eat), NULL);
		printf("%lu %i is eating\n",get_ms(p->last_eat, args), p->nr);
		usleep(args->time_to_eat * 1000);
		p->is_eating = 0;
	}
	if (args->philo_is_dead)
		return (1);
	gettimeofday(&(p->get_time), NULL);
	printf("%lu %i is sleeping\n",get_ms(p->get_time, args), p->nr);
	usleep(args->time_to_sleep * 1000);
	if (args->philo_is_dead)
		return (1);
	gettimeofday(&(p->get_time), NULL);
	printf("%lu %i is thinking\n",get_ms(p->get_time, args), p->nr);
	return (0);
}


void	*routine(void *philo)
{
	t_philo			*p;
	t_args			*args;

	p = (t_philo*) philo;
	args = get_args();
	gettimeofday(&(p->last_eat), NULL);
	if (args->min_nr_eat > 0)
	{
		while (p->nr_eat < args->min_nr_eat) {
			if (wait_for_fork(p, args))
				return (NULL);
			if (eat_sleep_think(p, args))
				return (NULL);
			p->nr_eat++;
		}
	}
	else {
		while (!(args->philo_is_dead))
		{
			if (wait_for_fork(p, args))
				return (NULL);
			if (eat_sleep_think(p, args))
				return (NULL);
		}
	}
	return (NULL);
}


/*
void	*routine(void *philo)
{
	t_philo			*p;
	t_args			*args;

	args = get_args();
	p = (t_philo*) philo;
	gettimeofday(&(p->last_eat), NULL);
	printf("%i. created: %lu\n", p->nr, get_ms(p->last_eat, args));
	return (NULL);
}
*/

void	init_threads()
{
	int		i;
	t_philo	*p;

	i = 0;
	p = get_ps()->nxt;
	gettimeofday(&(get_args()->start), NULL);
	while (i < get_args()->nr_philo)
	{
		pthread_mutex_init(&(p->m), NULL);
		if (pthread_create(&(p->t), NULL, &routine, (void *) p))
			return ;
		i++;
		p = p->nxt;
	}
	i = 0;
	p = get_ps()->nxt;
	while (i < get_args()->nr_philo)
	{
		if (pthread_join(p->t, NULL))
			return ; //save return value in second argument
		pthread_mutex_destroy(&(p->m));
		p = p->nxt;
		i++;
	}
}
