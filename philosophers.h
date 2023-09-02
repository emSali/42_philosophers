/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esali <esali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:05:57 by esali             #+#    #+#             */
/*   Updated: 2023/09/02 12:58:11 by esali            ###   ########.fr       */
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
	int				nr_eat;
	pthread_t		t;
	pthread_mutex_t	m;
	struct s_philo	*nxt;
	struct s_philo	*prv;
}		t_philo;

typedef struct	s_fork
{
	pthread_mutex_t	m;

}		t_fork;

typedef struct s_args
{
	int	nr_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_nr_eat;
}		t_args;

t_philo	*get_ps();
t_args	*get_args();
int		init_args(char **argv);
void	init_philos(int amount);
void	free_philos(int amount);
void	print_philos();
void	init_threads();
t_philo	*ft_lstnew(int number, t_philo *prv_philo);

#endif
