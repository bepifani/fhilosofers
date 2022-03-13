/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:29:45 by bepifani          #+#    #+#             */
/*   Updated: 2022/03/13 13:04:55 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <inttypes.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct s_philo2
{
	int				name;
	int				left_fork;
	int				right_fork;
	int				nb_eat;
	int				last_eat;
	int				death;
	pthread_mutex_t	eating;
	struct s_philo	*phil;
}	t_philo2;

typedef struct s_pfilo
{
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		nb_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	death_occur;
	t_philo2	*philosof;
}	t_philo;

//utils.c
int		ft_atoi(const char *str);

//philo.c
int		ft_parser(char **argv, t_philo *philo, int argc);
void	ft_init_philo2(t_philo *philo);
int		ft_init_mutex(t_philo *philo);
void	ft_init(t_philo *philo);

#endif