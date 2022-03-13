/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:29:33 by bepifani          #+#    #+#             */
/*   Updated: 2022/03/13 13:08:56 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_philo *philo)
{
	philo->forks = NULL;
	philo->philosof = NULL;
	philo->nb_philo = 0;
	philo->time_die = 0;
	philo->time_eat = 0;
	philo->time_sleep = 0;
	philo->nb_eat = 0;
}

int	ft_init_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_init(&philo->write, NULL);
	pthread_mutex_init(&philo->death_occur, NULL);
	pthread_mutex_lock(&philo->death_occur);
	philo->forks = malloc(sizeof(*(philo->forks)) * philo->nb_philo);
	if (!philo->forks)
		return (1);
	while (i < philo->nb_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	return (0);
}

void	ft_init_philo2(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		philo->philosof[i].name = i;
		philo->philosof[i].left_fork = (i + 1) % philo->nb_philo;
		philo->philosof[i].right_fork = i;
		philo->philosof[i].nb_eat = 0;
		philo->philosof[i].phil = philo;
		pthread_mutex_init(&philo->philosof[i].eating, NULL);
		i++;
	}	
}

int	ft_parser(char **argv, t_philo *philo, int argc)
{
	ft_init(philo);
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nb_eat = ft_atoi(argv[5]);
	philo->philosof = (t_philo2 *)malloc(sizeof(*(philo->philosof)) * (philo->nb_philo));
	if (!philo->philosof)
		return (1);
	ft_init_philo2(philo);
	return(ft_init_mutex(philo));
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	
	if (argc == 6 || argc == 5)
	{
		if (ft_parser(argv, &philo, argc))
		{
			// ft_clear();
			// ft_error();
			return (0);
		}
		ft_parser(argv, &philo, argc);
	}
	else
		write (1, "WRONG ARGUMENTS\n", 16);
	return(0);
}