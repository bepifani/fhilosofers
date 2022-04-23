/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:03:13 by bepifani          #+#    #+#             */
/*   Updated: 2022/04/23 21:19:23 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
}

long	get_current_time(long time)
{
	struct timeval	*start_time;
	time_t			current;

	start_time = malloc(sizeof(struct timeval) * 1);
	gettimeofday(start_time, NULL);
	current = start_time->tv_sec * 1000 + start_time->tv_usec / 1000;
	return (current - time);
}

void	ft_usleep(time_t milisec, long start_time)
{
	time_t	stop;
	time_t	start;

	stop = get_current_time(start_time) + milisec;
	start = get_current_time(start_time);
	while (start < stop)
	{
		usleep(10);
		start = get_current_time(start_time);
	}
}

int	check_param(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (0);
	if (!check_chars(argv))
	{
		printf("[ERROR] wrong arguments");
		return (0);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 \
	|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
	{
		printf("[ERROR] wrong arguments");
		return (0);
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
		{
			printf("[ERROR] wrong arguments");
			return (0);
		}
	}
	return (1);
}
