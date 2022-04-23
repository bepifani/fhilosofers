/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:58:44 by bepifani          #+#    #+#             */
/*   Updated: 2022/04/18 19:51:29 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_spec(void *p)
{
	t_philo2	*phil;
	int			i;
	int			en;

	phil = (t_philo2 *)p;
	while (1)
	{
		i = 0;
		en = 0;
		while (i < phil->nb_philo)
		{
			if (phil->philosof[i++].eat_counter >= phil->must_eat)
				en++;
		}
		if (en == phil->nb_philo)
			break ;
		usleep(100);
	}
	pthread_mutex_unlock(&phil->death_occur);
	return (NULL);
}

void	*ft_ob(void	*p)
{
	t_philo	*phil;

	phil = (t_philo *)p;
	while (1)
	{
		pthread_mutex_lock(&phil->eating_m);
		if (ft_get_time() > phil->death_lim)
		{
			ft_massage(phil, "DIED");
			pthread_mutex_unlock(&phil->eating_m);
			pthread_mutex_unlock(&phil->state->death_occur);
		}
		pthread_mutex_unlock(&phil->eating_m);
		usleep(1000);
	}
}

void	*ft_philo(void *p)
{
	t_philo		*self;
	pthread_t	tid;

	self = (t_philo *)p;
	self->last_eat = ft_get_time();
	self->death_lim = self->last_eat + self->state->time_die;
	pthread_create(&tid, NULL, ft_ob, p);
	pthread_detach(tid);
	if (self->name % 2 == 1 || (self->state->nb_philo % 2 == 1
			&& self->name == self->state->nb_philo - 1))
	{
		ft_massage(self, "THINKING");
		usleep(400);
	}
	while (1)
	{
		ft_eat(self);
		ft_massage(self, "SLEEPING");
		usleep(self->state->time_sleep * 1000);
		ft_massage(self, "THINKING");
	}
}

void	ft_massage(t_philo *philo, char *str)
{
	uint64_t	delta;
	static int	dead = 0;

	if (dead > 0)
		return ;
	delta = ft_get_time() - philo->state->start;
	pthread_mutex_lock(&philo->state->write);
	if (str[0] == 'D' && str[1] == 'I')
		dead = 1;
	printf("%llu %d %s\n", delta, philo->name + 1, str);
	pthread_mutex_unlock(&philo->state->write);
}

void	ft_eat(t_philo *self)
{
	pthread_mutex_lock(&self->state->forks[self->right_fork]);
	ft_massage(self, "TAKEN  RIGHT FORK");
	pthread_mutex_lock(&self->state->forks[self->left_fork]);
	ft_massage(self, "TAKEN LEFT FORK");
	pthread_mutex_lock(&self->eating_m);
	self->last_eat = ft_get_time();
	self->death_lim = self->last_eat + self->state->time_die;
	ft_massage(self, "EATING");
	usleep(self->state->time_eat * 1000);
	self->eat_counter++;
	pthread_mutex_unlock(&self->eating_m);
	pthread_mutex_unlock(&self->state->forks[self->left_fork]);
	pthread_mutex_unlock(&self->state->forks[self->right_fork]);
}
