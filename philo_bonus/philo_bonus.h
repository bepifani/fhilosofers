/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:53:04 by bepifani          #+#    #+#             */
/*   Updated: 2022/04/23 21:12:27 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define EXIT_DEAD 1
# define EXIT_ALIVE 0
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_env	t_env;

typedef struct s_philos	t_philos;

typedef struct s_philos
{
	int				eaten_meals;
	int				number;
	t_env			*env;
	time_t			time_to_die;
	pid_t			pid;
	pthread_t		dead;
}				t_philos;

typedef struct s_env
{
	int				nb_should_eat;
	int				nb_philos;
	int				dead;
	t_philos		*philos;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	sem_t			*print;
	sem_t			*check;
	sem_t			*forks;
}				t_env;

//utils_bonus.c
int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		ft_isspaces(char c);
int		getmaxmin(int currentValue, int currNum, int sign);
int		check_chars(char **argv);

//init_bonus.c
int		init_sem(t_env *env);
int		init_env(t_env *env, char **argv, int argc);
int		get_filos(t_env *env);

//utils2_bonus.c
long	get_time(void);
long	get_current_time(long time);
void	ft_usleep(time_t milisec, long start_time);
int		check_param(int argc, char **argv);

//action_bonus.c
void	take_forks(t_philos *philos);
void	eat(t_philos *philos);
void	p_sleep(t_philos *philos);
void	think(t_philos *philos);

//philo_bonus.c
void	*life_cycle(void *obj);
void	*check_dead(void *args);
void	end_programm(t_env *env);
int		run_programm(t_env *env);

#endif