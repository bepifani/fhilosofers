/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:29:45 by bepifani          #+#    #+#             */
/*   Updated: 2022/03/27 17:54:23 by bepifani         ###   ########.fr       */
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
	int				eat_counter;
	int				last_eat;
	uint64_t				death;
	pthread_mutex_t	eating;
	struct s_pfilo	*phil;
}	t_philo2;

typedef struct s_pfilo
{
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		nb_eat;
	uint64_t		time_start;
	t_philo2	*philosof;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	death_occur;
}	t_philo;

//utils.c
int		ft_atoi(const char *str);
void	*ft_spectator(void *tmp);
int		ft_check_philo(t_philo *philo);
uint64_t	get_time(void);
int	ft_error (char *text);

//philo.c
int		ft_parser(char **argv, t_philo *philo, int argc);
void	ft_init_philo2(t_philo *philo);
int		ft_init_mutex(t_philo *philo);
void	ft_init(t_philo *philo);

//utils2.c
int	ft_clear(t_philo *philo);

//philo2.c
void	*ft_philo(void *p);
void	*ft_ob(void *p);
void	ft_writing(t_philo2 *p, char *msg);
void	ft_eating(t_philo2 *p);

#endif