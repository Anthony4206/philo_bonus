/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:23:38 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/12 09:56:29 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "structs_bonus.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_error(char **argv)
{
	int	i;
	int	j;

	i = 0;
	if ((ft_strlen(argv[1]) == 1) && (argv[1][0] == '0'))
		return (1);
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
		}
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && (((size_t)-1) / size) < count)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	memset(ptr, '\0', count * size);
	return (ptr);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		neg;
	int		res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg = -neg;
		i++;
	}
	while (str[i] && ((str[i] >= '0') && (str[i] <= '9')))
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * neg);
}
