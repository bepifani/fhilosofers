/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:30:25 by bepifani          #+#    #+#             */
/*   Updated: 2022/03/27 18:12:18 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_clear(t_philo *philo)
{
	int	i;

	printf ("ft_clear\n");
	if (philo->forks)
	{
		i = 0;
		while (i < philo->nb_philo)
		{
			pthread_mutex_destroy(&philo->forks[i++]);
		}
		free(philo->forks);
	}
	if (philo->philosof)
	{
		i = 0;
		while (i < philo->nb_philo)
		{
			pthread_mutex_destroy(&philo->philosof[i++].eating);
		}
		free(philo->philosof);
	}
	pthread_mutex_destroy(&philo->write);
	pthread_mutex_destroy(&philo->death_occur);
	return (1);
}

