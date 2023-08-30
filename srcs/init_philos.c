/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:52:03 by esali             #+#    #+#             */
/*   Updated: 2023/08/30 19:34:12 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosophers.h"

t_philo	*get_ps()
{
	static t_philo	list;

	return (&list);
}

t_philo	*ft_lstnew(int number, t_philo *prv_philo)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->nr = number;
	new_philo->is_sleeping = 0;
	new_philo->is_eating = 0;
	new_philo->prv = prv_philo;
	new_philo->nxt = NULL;
	prv_philo->nxt = new_philo;
	return (new_philo);
}

/*void	init_philos(int amount)
{
	t_philo	*old_p;
	t_philo	*new_p;
	int		i;

	i = 0;
	old_p = get_ps()
	while (i < amount)
	{

	}
}*/
