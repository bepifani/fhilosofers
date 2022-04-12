/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:44:34 by bepifani          #+#    #+#             */
/*   Updated: 2022/04/12 19:26:59 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_clear(t_philo2 *p)
{
	int	i;

	i = 0;
	if (p->forks)
	{
		while (i < p->nb_philo)
			pthread_mutex_destroy(&p->forks[i++]);
		free(p->forks);
	}
	i = 0;
	if (p->philosof)
	{
		while (i < p->nb_philo)
			pthread_mutex_destroy(&p->philosof[i++].eating_m);
		free(p->philosof);
	}
	pthread_mutex_destroy(&p->write);
	pthread_mutex_destroy(&p->death_occur);
	return (1);
}

int		ft_strlen(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_error(char *str)
{
	write (1, str, ft_strlen(str));
	write (1, "\n", 1);
	return (1);
}

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
