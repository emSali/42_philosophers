/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:07:44 by esali             #+#    #+#             */
/*   Updated: 2023/09/03 17:35:04 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	wait_for_fork(t_philo *p)
{
	t_args	*args;

	args = get_args();
	while(p->prv->is_eating || p->nxt->is_eating)
	{
		gettimeofday(&(p->get_time), NULL);
		if ((p->get_time.tv_usec - p->last_eat.tv_usec) > args->time_to_die \
		&& p->nr_eat < args->min_nr_eat)
		{
			args->philo_is_dead = 1;
			printf("%d %i died\n", p->get_time.tv_usec, p->nr);
			return (1);
		}
		usleep(10);
	}
	if (args->philo_is_dead)
		return (1);
	return (0);
}

int	eat_sleep_think(t_philo *p)
{
	t_args	*args;

	args = get_args();
	pthread_mutex_lock(&(p->m));
	if (!p->prv->is_eating && !p->nxt->is_eating)
	{
		p->is_eating = 1;
		gettimeofday(&(p->last_eat), NULL);
		printf("%d %i is eating\n", p->last_eat.tv_usec, p->nr);
		usleep(args->time_to_eat);
		p->is_eating = 0;
	}
	if (args->philo_is_dead)
		return (1);
	pthread_mutex_unlock(&(p->m));
	gettimeofday(&(p->get_time), NULL);
	printf("%d %i is sleeping\n", p->get_time.tv_usec, p->nr);
	usleep(args->time_to_sleep);
	if (args->philo_is_dead)
		return (1);
	gettimeofday(&(p->get_time), NULL);
	printf("%d %i is thinking\n", p->get_time.tv_usec, p->nr);
	return (0);
}

void	*routine(void *philo)
{
	t_philo			*p;
	t_args			*args;

	p = (t_philo*) philo;
	args = get_args();
	while (p->nr_eat < args->min_nr_eat) {
		if (wait_for_fork(p))
			return (NULL);
		if (eat_sleep_think(p))
			return (NULL);
		p->nr_eat++;
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
		gettimeofday(&(p->last_eat), NULL);
		pthread_create(&(p->t), NULL, &routine, (void *) p);
		i++;
		p = p->nxt;
	}
	i = 0;
	p = get_ps()->nxt;
	while (i < get_args()->nr_philo)
	{
		pthread_join(p->t, NULL); //save return value in second argument
		pthread_mutex_destroy(&(p->m));
		p = p->nxt;
		i++;
	}
}
