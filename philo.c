/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:20:37 by bepifani          #+#    #+#             */
/*   Updated: 2022/04/12 22:14:39 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init3(t_philo2 *p)
{
	int	i;

	pthread_mutex_init(&p->write, NULL);
	pthread_mutex_init(&p->death_occur, NULL);
	pthread_mutex_lock(&p->death_occur);
	p->forks = malloc(sizeof(*(p->forks)) * p->nb_philo);
	if (!p->forks)
		return (1);
	i = 0;
	while (i < p->nb_philo)
		pthread_mutex_init(&p->forks[i++], NULL);
	return (0);
}

void	ft_init2(t_philo2 *p)
{
	int	i;

	i = 0;
	while (i < p->nb_philo)
	{
		p->philosof[i].name = i;
		p->philosof[i].left_fork = i;
		p->philosof[i].right_fork= i + 1;
		p->philosof[i].eat_counter = i;
		p->philosof[i].state = p;
		pthread_mutex_init(&p->philosof[i].eating_m, NULL);
		i++;
	}
}

int	ft_init(t_philo2 *p, char **argv, int argc)
{
	p->forks = NULL;
	p->philosof = NULL;
	p->nb_philo = ft_atoi(argv[1]);
	p->time_die = ft_atoi(argv[2]);
	p->time_eat = ft_atoi(argv[3]);
	p->time_die = ft_atoi(argv[4]);
	p->must_eat = 0;
	if (argc == 6)
		p->must_eat = ft_atoi(argv[5]);
	p->philosof = (t_philo *)malloc(sizeof(*(p->philosof)) * p->nb_philo);
	if (!p->philosof)
		return (1);
	ft_init2(p);
	return (ft_init3(p));
}

int	ft_philosof(t_philo2 *p)
{
	int			i;
	void		*ph;
	pthread_t	time;

	i = 0;
	p->start = ft_get_time();
	if (p->must_eat > 0)
	{
		ph = (void *)p;
		pthread_create(&time, NULL, ft_spec, ph);
		pthread_detach(time);
	}
	while (i < p->nb_philo)
	{
		ph = (void *)(&p->philosof[i]);
		pthread_create(&time, NULL, ft_philo, ph);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo2	philo;

	if (argc != 5 && argc != 6)
		return (ft_error("[ERROR] Wrond arguments"));
	if (ft_init(&philo, argv, argc))
		return (ft_clear(&philo) && ft_error("[ERROR] Wrond arguments"));
	if (ft_philosof((&philo)))
		return (ft_clear(&philo) && ft_error("[ERROR] Wrond arguments"));
	pthread_mutex_lock(&philo.death_occur);
	pthread_mutex_unlock(&philo.death_occur);
	ft_clear(&philo);
	return (0);
}
