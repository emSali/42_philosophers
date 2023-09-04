/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:05:57 by esali             #+#    #+#             */
/*   Updated: 2023/09/04 18:26:28 by esali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	struct s_fork	*left;
	struct s_fork	*right;
	struct s_args	*args;
	pthread_t		t;
}		t_philo;

typedef struct	s_fork
{
	pthread_mutex_t	m;
	int				is_busy;
}		t_fork;

typedef struct s_args
{
	int		nr_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		min_nr_eat;
	int		philo_is_dead;
}		t_args;

t_args	*get_args();
int		init_args(char **argv);
t_philo	**init_philos(t_args *args);
void	free_philos(t_philo **ps);
void	start_philos(t_philo **ps, t_args *args);

#endif