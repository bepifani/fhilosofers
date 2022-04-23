/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:06:23 by bepifani          #+#    #+#             */
/*   Updated: 2022/04/23 21:17:26 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philos *philos)
{
	sem_wait(philos->env->forks);
	sem_wait(philos->env->print);
	printf("%ld\tPHILO %d TAKEN 1 FORK\n", \
		get_current_time(philos->env->start_time), philos->number);
	sem_post(philos->env->print);
	sem_wait(philos->env->forks);
	sem_wait(philos->env->print);
	printf("%ld\tPHILO %d TAKEN 2 FORK\n", \
		get_current_time(philos->env->start_time), philos->number);
	sem_post(philos->env->print);
}

void	eat(t_philos *philos)
{
	sem_wait(philos->env->print);
	printf("%ld\tPHILO %d EATING\n", \
		get_current_time(philos->env->start_time), philos->number);
	sem_post(philos->env->print);
	ft_usleep(philos->env->time_to_eat, philos->env->start_time);
	sem_wait(philos->env->check);
	philos->time_to_die = get_time();
	philos->eaten_meals++;
	sem_post(philos->env->check);
	sem_post(philos->env->forks);
	sem_post(philos->env->forks);
}

void	p_sleep(t_philos *philos)
{
	sem_wait(philos->env->print);
	printf("%ld\tPHILO %d SLEEPING\n", \
		get_current_time(philos->env->start_time), philos->number);
	sem_post(philos->env->print);
	ft_usleep(philos->env->time_to_sleep, philos->env->start_time);
}

void	think(t_philos *philos)
{
	sem_wait(philos->env->print);
	printf("%ld\tPHILO %d THINKING\n", \
		get_current_time(philos->env->start_time), philos->number);
	sem_post(philos->env->print);
}
