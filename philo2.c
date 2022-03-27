/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:29:46 by bepifani          #+#    #+#             */
/*   Updated: 2022/03/27 18:12:01 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *p)
{
	t_philo2	*philo;
	pthread_t	t;

	printf ("ft_philo\n");
	philo = (t_philo2 *)p;
	philo->last_eat = get_time();
	philo->death = philo->last_eat + philo->phil->time_die;
	pthread_create(&t, NULL, ft_ob, p);
	pthread_detach(t);
	if (philo->name % 2 == 1 || (philo->phil->time_die % 2 == 1 && philo->name == philo->phil->nb_philo))
	{
		ft_writing(philo, "THINK");
		usleep(philo->phil->nb_philo * 500);
	}
	while (1)
	{
		ft_eating(philo);
		ft_writing (philo, "SLEEP");
		usleep (philo->phil->nb_philo * 1000);
		ft_writing (philo, "THINK");
	}
}

void *ft_ob(void *p)
{
	t_philo2	*philo;

	printf ("ft_ob\n");
	philo=(t_philo2 *)p;
	while (1)
	{
		pthread_mutex_lock(&philo->eating);
		if (get_time() > philo->death)
		{
			ft_writing(philo, "DIED");
			pthread_mutex_unlock(&philo->eating);
			pthread_mutex_unlock(&philo->phil->death_occur);
		}
		pthread_mutex_unlock(&philo->eating);
		usleep(1000);
	}
}

void	ft_eating(t_philo2 *p)
{
	printf ("ft_eating\n");
	pthread_mutex_lock(&p->phil->forks[p->right_fork]);
	ft_writing(p, "TAKEN");
	pthread_mutex_lock(&p->phil->forks[p->left_fork]);
	ft_writing(p, "TAKEN");
	pthread_mutex_lock(&p->eating);
	p->last_eat = get_time();
	p->death = p->last_eat + p->phil->time_die;
	ft_writing(p, "EATING");
	usleep(p->phil->nb_eat * 1000);
	p->eat_counter++;
	pthread_mutex_unlock(&p->eating);
	pthread_mutex_unlock(&p->phil->forks[p->left_fork]);
	pthread_mutex_unlock(&p->phil->forks[p->right_fork]);
}

void	ft_writing(t_philo2 *p, char *msg)
{
	uint64_t	delta;
	static int	dead = 0;

	printf ("ft_writing\n");
	if (dead > 0)
		return ;
	delta = get_time() - p->phil->time_start;
	pthread_mutex_lock(&p->phil->write);
	if (msg[0] == 'd' && msg[1] == 'i')
		dead = 1;
	printf("%llu %d %s\n", delta, p->name + 1, msg);
	pthread_mutex_unlock(&p->phil->write);
}