/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:07:44 by esali             #+#    #+#             */
/*   Updated: 2023/09/02 20:11:14 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*routine(void *philo)
{
	t_philo			*p;
	t_args			*args;

	p = (t_philo*) philo;
	args = get_args();
	if (args->min_nr_eat){
		while (p->nr_eat < args->min_nr_eat) {
			while(p->prv->is_eating || p->nxt->is_eating)
			{
			}
			pthread_mutex_lock(&(p->m));
			if (!p->prv->is_eating && !p->nxt->is_eating)
			{
				p->is_eating = 1;
				gettimeofday(&(p->last_eat), NULL);
				printf("%d %i is eating\n", p->last_eat.tv_usec, p->nr);
				usleep(args->time_to_eat);
				p->is_eating = 0;
				p->nr_eat++;
			}
			pthread_mutex_unlock(&(p->m));
			gettimeofday(&(p->get_time), NULL);
			printf("%d %i is sleeping\n", p->get_time.tv_usec, p->nr);
			usleep(args->time_to_sleep);
			gettimeofday(&(p->get_time), NULL);
			printf("%d %i is thinking\n", p->get_time.tv_usec, p->nr);
		}
		//printf("Philo nr. %i ate %i times\n", p->nr, p->nr_eat);
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
