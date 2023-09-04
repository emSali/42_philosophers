/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:07:44 by esali             #+#    #+#             */
/*   Updated: 2023/09/04 15:12:38 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	wait_for_fork(t_philo *p, t_args *args)
{
	int		i;

	i = 0;
	if (args->philo_is_dead)
		return (1);
	while(p->prv->is_eating || p->nxt->is_eating || i == 0)
	{
		gettimeofday(&(p->get_time), NULL);
		//printf("%i:	diff:%ld\n",p->nr, p->get_time.tv_usec - p->last_eat.tv_usec);
		if ((p->get_time.tv_usec - p->last_eat.tv_usec) > args->time_to_die \
		&& (args->min_nr_eat == 0 || p->nr_eat < args->min_nr_eat))
		{
			args->philo_is_dead = 1;
			printf("%ld %i died\n", p->get_time.tv_usec, p->nr);
			return (1);
		}
		usleep(1);
		i = 1;
	}
	if (args->philo_is_dead)
		return (1);
	return (0);
}

void	eat(t_philo *p, t_args *args)
{
	pthread_mutex_lock(&(p->m));
	if (!(p->prv->is_eating) && !(p->nxt->is_eating))
	{
		p->is_eating = 1;
		pthread_mutex_unlock(&(p->m));
		gettimeofday(&(p->last_eat), NULL);
		printf("%ld %i is eating\n", p->last_eat.tv_usec, p->nr);
		usleep(args->time_to_eat);
		p->is_eating = 0;
	}
}

int	eat_sleep_think(t_philo *p, t_args *args)
{
	if (!(p->prv->is_eating) && !(p->nxt->is_eating))
	{
		pthread_mutex_lock(&(p->m));
		p->is_eating = 1;
		pthread_mutex_unlock(&(p->m));
		gettimeofday(&(p->last_eat), NULL);
		printf("%ld %i is eating\n", p->last_eat.tv_usec, p->nr);
		usleep(args->time_to_eat);
		p->is_eating = 0;
	}
	if (args->philo_is_dead)
		return (1);
	gettimeofday(&(p->get_time), NULL);
	printf("%ld %i is sleeping\n", p->get_time.tv_usec, p->nr);
	usleep(args->time_to_sleep * 0.75);
	if (args->philo_is_dead)
		return (1);
	gettimeofday(&(p->get_time), NULL);
	printf("%ld %i is thinking\n", p->get_time.tv_usec, p->nr);
	//usleep(5);
	return (0);
}

void	*routine(void *philo)
{
	t_philo			*p;
	t_args			*args;

	p = (t_philo*) philo;
	args = get_args();
	//gettimeofday(&(p->last_eat), NULL);
	//eat(p, args);
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

void	init_threads()
{
	int		i;
	t_philo	*p;

	i = 0;
	p = get_ps()->nxt;
	while (i < get_args()->nr_philo)
	{
		pthread_mutex_init(&(p->m), NULL);
		i++;
		p = p->nxt;
	}
	i = 0;
	p = get_ps()->nxt;
	while (i < get_args()->nr_philo)
	{
		gettimeofday(&(p->last_eat), NULL);
		printf("%i: %ld\n", p->nr, p->last_eat.tv_usec);
		if (pthread_create(&(p->t), NULL, &routine, (void *) p))
			return ;
		gettimeofday(&(p->last_eat), NULL);
		printf("%i: %ld\n", p->nr, p->last_eat.tv_usec);
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
