/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:24:04 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/12 11:31:30 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#include "structs_bonus.h"

long int	ft_diff(struct timeval diff)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec - diff.tv_sec) * 1000000)
		+ (tv.tv_usec - diff.tv_usec));
}

long int	ft_death_diff(long int now, long int last)
{
	return (now - last);
}

void	ft_usleep(t_ctx *rules, long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	while (ft_diff(tv) <= time && !rules->is_die)
		usleep(50);
}

long int	ft_time(long int start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (end.tv_sec * 1000 + end.tv_usec / 1000 - start);
}

void	ft_lock_print(t_ctx *rules, int philo, char *msg)
{
	sem_wait(rules->ths.print);
	if (!rules->is_die)
	{
		printf("%ld ", ft_time(rules->start));
		printf("%d ", philo + 1);
		printf("%s\n", msg);
	}
	sem_post(rules->ths.print);
}
