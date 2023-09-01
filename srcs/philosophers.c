/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:07:44 by esali             #+#    #+#             */
/*   Updated: 2023/09/01 17:06:49 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*print_nr(void *philo)
{
	t_philo	*p;
	//int			i;

	p = (t_philo*) philo;
	//pthread_mutex_lock(&(p->m));
	//i = *(int *) philo;
	printf("Philo nr. %i\n", p->nr);
	//pthread_mutex_unlock(&(p->m));
	return (NULL);
}

t_philo	*dup_philo(t_philo *p)
{
	t_philo *new_p;

	new_p = ft_lstnew(p->nr, p->prv);
	new_p->nxt = p->nxt;
	return (new_p);
}

void	init_threads()
{
	int		i;
	t_philo	*p;
	//t_philo	*tmp_p;

	i = 0;
	p = get_ps()->nxt;
	while (i < get_args()->nr_philo)
	{
		//tmp_p = dup_philo(p);
		pthread_mutex_init(&(p->m), NULL);
		printf("%i\n", p->nr);
		pthread_create(&(p->t), NULL, &print_nr, &p);
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
