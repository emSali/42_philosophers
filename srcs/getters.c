/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:08:15 by esali             #+#    #+#             */
/*   Updated: 2023/09/01 16:33:51 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/* Static variables have the property of preserving
their value even after they are out of their scope*/
t_args	*get_args()
{
	static t_args	args;

	return (&args);
}

t_philo	*get_ps()
{
	static t_philo	list;

	return (&list);
}
