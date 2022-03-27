/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:34:14 by bepifani          #+#    #+#             */
/*   Updated: 2022/03/27 18:13:47 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (*str == ' ' || *str == '\n' || *str == '\v'
		|| *str == '\t' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		b++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		i = i * 10 + (*str - 48);
		str++;
	}
	if (b == 1)
		i = i * (-1);
	return (i);
}

void	*ft_spectator(void *tmp)
{
	t_philo	*p;
	int		i;
	int		j;

	printf ("ft_spectator\n");
	p = (t_philo *)tmp;
	while (1)
	{
		i = 0;
		j = 0;
		while (i < p->nb_philo)
		{
			if (p->philosof[i++].eat_counter >= p->nb_eat)
			{
				j++;
			}
		}
		if (j == p->nb_philo)
			break ;
		usleep (2000);
	}
	pthread_mutex_unlock(&p->death_occur);
	return (NULL);
}

int	ft_check_philo(t_philo *philo)
{
	int			i;
	pthread_t	time;
	void		*p;

	i = 0;
	printf ("ft_check_philo\n");
	philo->time_start = get_time();
	//printf ("%llu\n", philo->time_start);
	if (philo->nb_eat > 0)
	{
		p = (void *)philo;
		pthread_create(&time, NULL, ft_spectator, p);
		pthread_detach(time);
	}
	while (i < philo->nb_philo)
	{
		p = (void *)(&philo->philosof[i]);
		pthread_create(&time, NULL, ft_philo, philo);
		i++;
	}
	return (0);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	printf ("get_time\n");
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_error(char *text)
{
	printf ("ERROR - %s\n", text);
	return (1);
}
