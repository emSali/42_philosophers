/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:05:57 by esali             #+#    #+#             */
/*   Updated: 2023/09/02 19:54:13 by esali            ###   ########.fr       */
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
	int				is_sleeping;
	int				is_dead;
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
	int		nr_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		min_nr_eat;
}		t_args;

t_philo	*get_ps();
t_args	*get_args();
int		init_args(char **argv);
void	init_philos(int amount);
void	free_philos(int amount);
void	print_philos();
void	init_threads();

#endif
