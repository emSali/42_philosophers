/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:52:03 by esali             #+#    #+#             */
/*   Updated: 2023/09/02 19:52:20 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosophers.h"

t_philo	*ft_lstnew(int number, t_philo *prv_philo)
{
	t_philo	*new_philo;
	//struct timeval	last_eat;
	//struct timeval	get_time;

	new_philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->nr_eat = 0;
	new_philo->nr = number;
	new_philo->is_sleeping = 0;
	new_philo->is_eating = 0;
	//gettimeofday(&(new_philo->get_time), NULL);
	new_philo->prv = prv_philo;
	new_philo->nxt = NULL;
	prv_philo->nxt = new_philo;
	return (new_philo);
}

void	init_philos(int amount)
{
	t_philo	*old_p;
	t_philo	*first_p;
	int		i;

	i = 0;
	old_p = get_ps();
	while (i < amount)
	{
		old_p = ft_lstnew(i + 1, old_p);
		i++;
	}
	first_p = get_ps()->nxt;
	first_p->prv = old_p;
	old_p->nxt = first_p;
}

void	free_philos(int amount)
{
	t_philo	*node;
	t_philo	*tmp;
	int		i;

	i = 0;
	node = get_ps()->nxt;
	while (i < amount)
	{
		tmp = node->nxt;
		free(node);
		node = tmp;
		i++;
	}
	get_ps()->nxt = NULL;
}

void	print_philos()
{
	t_philo	*ps;

	ps = get_ps()->nxt;
	while (ps->nr < ps->nxt->nr)
	{
		printf("Philo nr. %i\n", ps->nr);
		ps = ps->nxt;
	}
	printf("Philo nr. %i\n", ps->nr);
}
