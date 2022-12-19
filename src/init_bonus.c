/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:29:01 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/12 11:41:32 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

#include "structs_bonus.h"
#include "philo_bonus.h"
#include "utils_bonus.h"

void	ft_free(t_ctx ctx)
{
	int	i;

	i = -1;
	while (++i < ctx.nb_philo)
		free(ctx.philo[i].last_diner);
	free(ctx.philo);
}

t_ctx	ft_parse(char **argv)
{
	t_ctx			ret;
	struct timeval	tv;

	ret.nb_philo = ft_atoi(argv[1]);
	ret.time_die = ft_atoi(argv[2]);
	ret.time_eat = ft_atoi(argv[3]);
	ret.time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		ret.nb_diner = ft_atoi(argv[5]);
	else
		ret.nb_diner = -1;
    ret.is_die = 0;
	gettimeofday(&tv, NULL);
	ret.start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	ret.sem = ft_init_sem(ret);
	ret.philo = ft_init_philo(&ret);

	return (ret);
}

t_sem	ft_init_sem(t_ctx ctx)
{
	t_sem	ret;

	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/checker");
	ret.forks = sem_open("/forks", O_CREAT, 644, ctx.nb_philo);
	ret.print = sem_open("/print", O_CREAT, 644, 1);
	ret.checker = sem_open("/checker", O_CREAT, 644, 1);
	return (ret);
}

t_philos	*ft_init_philo(t_ctx *ctx)
{
	t_philos	*ret;
	int			i;

	ret = ft_calloc(ctx->nb_philo, sizeof(t_philos));
	i = -1;
	while (++i < ctx->nb_philo)
	{
		ret[i].philo_id = i;
		ret[i].last_diner = ft_calloc(1, sizeof(long int));
        ret[i].nb_diner = 0;
    	ret[i].start = ctx->start;
        ret[i].is_die = 0;
		ret[i].rules = ctx;
	}
	return (ret);
}
