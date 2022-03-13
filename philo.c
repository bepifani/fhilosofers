/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:29:33 by bepifani          #+#    #+#             */
/*   Updated: 2022/03/12 17:46:58 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_philo *philo)
{
	philo->nb_philo = 0;
	philo->time_die = 0;
	philo->time_eat = 0;
	philo->time_sleep = 0;
	philo->nb_eat = 0;
}

void	ft_parser(char **argv, t_philo *philo)
{
	ft_init(philo);
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->nb_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	
	if (argc == 6)
	{
		ft_parser(argv, &philo);
	}
	else
		write (1, "WRONG ARGUMENTS\n", 16);
	return(0);
}