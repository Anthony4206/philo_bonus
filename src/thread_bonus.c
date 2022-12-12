/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:22:52 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/12 11:30:39 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#include "structs_bonus.h"
#include "philo_bonus.h"
#include "utils_bonus.h"

void	ft_create_thread(t_ctx ctx)
{
	int			i;

	i = -1;
	while (++i < ctx.nb_philo)
	{
		ctx.pid[i] = fork();
		if (ctx.pid[i] == 0)
			pthread_create(&ctx.ths.th[i], NULL, ft_philo_func, &ctx.philo[i]);
	}
	if (ctx.nb_philo % 2)
		printf("%ld %d is thinking\n", ft_time(ctx.start), ctx.nb_philo);
}

void	ft_join_thread(t_ctx ctx)
{
	int	i;

	i = -1;
	while (++i < ctx.nb_philo)
		pthread_join(ctx.ths.th[i], NULL);
	i = -1;
	sem_close(ctx.ths.forks);
	sem_close(ctx.ths.print);
	sem_unlink("/forks");
	sem_unlink("/print");
}

void	ft_eat(t_philos *philo)
{
	sem_wait(philo->rules->ths.forks);
	sem_wait(philo->rules->ths.forks);
	ft_lock_print(philo->rules, philo->philo, "has taken a fork");
	ft_lock_print(philo->rules, philo->philo, "has taken a fork");
	ft_lock_print(philo->rules, philo->philo, "is eating");
	*(philo->last_diner) = ft_time(philo->rules->start);
	ft_usleep(philo->rules, philo->rules->time_eat * 1000);
	sem_post(philo->rules->ths.forks);
	sem_post(philo->rules->ths.forks);
}

void	*ft_philo_func(void *v_philo)
{
	t_philos	*philo;
	int			nb_diner;

	philo = (t_philos *)v_philo;
	nb_diner = 0;
	if (philo->philo % 2)
	{
		ft_lock_print(philo->rules, philo->philo, "is thinking");
		ft_usleep(philo->rules, 10000);
	}
	while (1)
	{
		ft_eat(philo);
		if ((++nb_diner && nb_diner == philo->rules->nb_diner)
			|| philo->rules->is_die)
			break ;
		ft_lock_print(philo->rules, philo->philo, "is sleeping");
		ft_usleep(philo->rules, philo->rules->time_sleep * 1000);
		ft_lock_print(philo->rules, philo->philo, "is thinking");
	}
	return (NULL);
}
