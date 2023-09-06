/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:31:04 by esali             #+#    #+#             */
/*   Updated: 2023/09/05 18:42:45 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int				nr;
	int				is_eating;
	int				nr_eat;
	struct timeval	last_eat;
	struct timeval	get_time;
	pthread_t		t;
	pthread_mutex_t	m;
	struct s_philo	*nxt;
	struct s_philo	*prv;
}		t_philo;

typedef struct s_args
{
	struct timeval	start;
	int				nr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_nr_eat;
	int				philo_is_dead;
}		t_args;

t_philo	*get_ps();
t_args	*get_args();
int		init_args(char **argv);
void	init_philos(int amount);
void	free_philos(int amount);
void	init_threads();

#endif
