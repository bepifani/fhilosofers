/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 17:17:26 by bepifani          #+#    #+#             */
/*   Updated: 2022/04/23 21:12:53 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	value;
	int	sign;

	sign = 1;
	value = 0;
	while (ft_isspaces(*str) && *str != '\0')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = sign * (-1);
	if (!*str)
		return (-1);
	if (*str >= '0' && *str <= '9')
	{
		while (*str && (*str >= '0' && *str <= '9'))
		{
			if (value <= 214748364)
				value = value * 10 + (*str - '0');
			else
				return (value = getmaxmin(value, *str - '0', sign));
			str++;
		}
	}
	return (value * sign);
}

int	ft_isspaces(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	getmaxmin(int currentValue, int currNum, int sign)
{
	if ((currentValue > 214748364)
		|| (currentValue == 214748364 && currNum > 8))
	{
		if (sign > 0)
			return (-1);
		if (sign < 0)
			return (0);
	}
	if (currentValue <= 214748364 && currNum <= 7)
		return ((currentValue * 10 + currNum) * sign);
	if (currentValue == 214748364 && currNum == 8)
	{
		if (sign > 0)
			return ((currentValue * 10 + 7) * sign);
		if (sign < 0)
			return ((currentValue * 10 + currNum) * sign);
	}
	return (0);
}

int	check_chars(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		if (argv[i][++j] != '+' && argv[i][j] != '-' && !ft_isdigit(argv[i][j]))
			return (0);
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (0);
	}
	return (1);
}
