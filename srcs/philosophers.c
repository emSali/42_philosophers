/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:07:44 by esali             #+#    #+#             */
/*   Updated: 2023/09/02 13:00:09 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*print_nr(void *philo)
{
	t_philo	*p;

	p = (t_philo*) philo;
	printf("Philo nr. %i\n", p->nr);
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
		pthread_create(&(p->t), NULL, &print_nr, (void *) p);
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
