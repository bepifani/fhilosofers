/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:53:25 by bepifani          #+#    #+#             */
/*   Updated: 2022/04/23 21:15:03 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*life_cycle(void *obj)
{
	t_philos	*philos;

	philos = (t_philos *)obj;
	pthread_create(&philos->dead, NULL, check_dead, (void *)philos);
	if (philos->number % 2 == 0)
		ft_usleep(philos->env->time_to_eat / 10, philos->env->start_time);
	while (!(philos->env->dead))
	{
		take_forks(philos);
		eat(philos);
		if (philos->eaten_meals >= philos->env->nb_should_eat)
			break ;
		p_sleep(philos);
		think(philos);
	}
	pthread_join(philos->dead, NULL);
	exit(EXIT_ALIVE);
	return (obj);
}

void	*check_dead(void *args)
{
	t_philos	*philos;

	philos = (t_philos *)args;
	while (!philos->env->dead && philos->eaten_meals \
	< philos->env->nb_should_eat)
	{
		sem_wait(philos->env->check);
		if (get_time() - philos->time_to_die > philos->env->time_to_die)
		{
			philos->env->dead = 1;
			sem_wait(philos->env->print);
			printf("%ld\t%d PHILO DEAD\n", \
			get_current_time(philos->env->start_time), philos->number);
			exit(EXIT_DEAD);
		}
		sem_post(philos->env->check);
	}
	return (NULL);
}

void	end_programm(t_env *env)
{
	int	i;
	int	status;

	i = -1;
	while (++i < env->nb_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == EXIT_DEAD)
		{
			i = -1;
			while (++i < env->nb_philos)
				kill(env->philos[i].pid, SIGTERM);
			break ;
		}
	}
	sem_close(env->print);
	sem_close(env->check);
	sem_close(env->forks);
	sem_unlink("/print");
	sem_unlink("/check");
	sem_unlink("/forks");
	free(env->philos);
}

int	run_programm(t_env *env)
{
	int	i;

	i = -1;
	env->start_time = get_time();
	while (++i < env->nb_philos)
	{
		env->philos[i].time_to_die = env->start_time;
		env->philos[i].pid = fork();
		if (env->philos[i].pid == -1)
			exit(EXIT_FAILURE);
		if (env->philos[i].pid == 0)
			life_cycle((void *)&env->philos[i]);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (!check_param(argc, argv))
		return (0);
	if (!init_env(&env, argv, argc))
		return (0);
	run_programm(&env);
	end_programm(&env);
	return (1);
}
