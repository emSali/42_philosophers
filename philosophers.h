/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:05:57 by esali             #+#    #+#             */
/*   Updated: 2023/08/30 19:20:26 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>

typedef struct	s_philo
{
	int				nr;
	int				is_eating;
	int				is_sleeping;
	pthread_t		t;
	pthread_mutex_t	m;
	struct s_philo	*nxt;
	struct s_philo	*prv;
}		t_philo;

int		*init_args(char **argv, int nr);
t_philo	*get_ps();


#endif
