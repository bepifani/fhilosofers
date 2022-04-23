/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:20:25 by bepifani          #+#    #+#             */
/*   Updated: 2022/04/18 19:51:17 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>
# include <inttypes.h>

typedef struct s_philo
{
	int				name;
	int				left_fork;
	int				right_fork;
	int				eat_counter;
	uint64_t		last_eat;
	uint64_t		death_lim;
	pthread_mutex_t	eating_m;
	struct s_philo2	*state;
}	t_philo;

typedef struct s_philo2
{
	int				nb_philo;
	int				must_eat;
	t_philo			*philosof;
	uint64_t		start;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	death_occur;
}	t_philo2;

//philo2.c
void		*ft_spec(void *p);
void		*ft_philo(void *p);
void		*ft_ob(void	*p);
void		ft_massage(t_philo *philo, char *msg);
void		ft_eat(t_philo *self);

//philo.c
int			ft_init(t_philo2 *p, char **argv, int argc);
void		ft_init2(t_philo2 *p);
int			ft_init3(t_philo2 *p);
int			ft_philosof(t_philo2 *p);

//utils.c
int			ft_atoi(const char *str);
int			ft_error(char *str);
int			ft_strlen(char *str);
int			ft_clear(t_philo2 *p);
uint64_t	ft_get_time(void);

#endif