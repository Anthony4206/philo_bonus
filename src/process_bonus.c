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

void	ft_terminate_diner(t_philos *philo)
{
	long	round_time;
	long	finish_time;

	round_time = philo->rules->time_eat + philo->rules->time_sleep;
	finish_time = round_time * (philo->rules->nb_diner);
	if (*(philo->last_diner) < (finish_time - philo->rules->time_eat))
	{
		ft_lock_print(philo->rules, philo->philo_id, "is sleeping");
		ft_usleep(philo->rules, philo->rules->time_sleep * 1000);
		if (philo->rules->time_sleep < philo->rules->time_eat)
			ft_lock_print(philo->rules, philo->philo_id, "is thinking");
	}
}

void	*ft_death(void *philo)
{
    t_philos    *res;

    res = (t_philos *)philo;
	while (1)
	{
        if (res->rules->nb_diner > 0 && (ft_time(res->start)
            >= ((res->rules->nb_diner - 1) * (res->rules->time_eat
                + res->rules->time_sleep) + res->rules->time_die)))
			break ;
        sem_wait(res->rules->sem.checker);
        if (ft_death_diff(ft_time(res->start), *(res->last_diner))
            > res->rules->time_die)
        {
            sem_post(res->rules->sem.checker);
            ft_lock_print(res->rules, res->philo_id, "died");
            res->is_die = 1;
            sem_wait(res->rules->sem.print);
            exit(EXIT_FAILURE);
        }
        sem_post(res->rules->sem.checker);
	}
    exit(EXIT_FAILURE);
}

void	ft_eat(t_philos *philo)
{
	sem_wait(philo->rules->sem.forks);
	sem_wait(philo->rules->sem.forks);
	ft_lock_print(philo->rules, philo->philo_id, "has taken a fork");
	ft_lock_print(philo->rules, philo->philo_id, "has taken a fork");
	ft_lock_print(philo->rules, philo->philo_id, "is eating");
    sem_wait(philo->rules->sem.checker);
	*(philo->last_diner) = ft_time(philo->rules->start);
    sem_post(philo->rules->sem.checker);
	ft_usleep(philo->rules, philo->rules->time_eat * 1000);
	sem_post(philo->rules->sem.forks);
	sem_post(philo->rules->sem.forks);
}

void    ft_func_philo(t_philos *philo)
{
    pthread_create(&philo->th, NULL, ft_death, philo);
    if (philo->rules->nb_philo % 2)
		printf("%ld %d is thinking\n",
            ft_time(philo->start), philo->rules->nb_philo);
	if (philo->philo_id % 2)
	{
		ft_lock_print(philo->rules, philo->philo_id, "is thinking");
		ft_usleep(philo->rules, 10000);
	}
	while (1)
	{
		ft_eat(philo);
		if ((++philo->nb_diner && philo->nb_diner == philo->rules->nb_diner)
			|| philo->rules->is_die)
        {
            if (!philo->rules->is_die && philo->rules->nb_diner > 0)
				ft_terminate_diner(philo);
			break ;
        }
		ft_lock_print(philo->rules, philo->philo_id, "is sleeping");
		ft_usleep(philo->rules, philo->rules->time_sleep * 1000);
		ft_lock_print(philo->rules, philo->philo_id, "is thinking");
	}
    pthread_join(philo->th, NULL);
}

void	ft_process_launcher(t_ctx *ctx)
{
    int i;

    i = -1;
    while (++i < ctx->nb_philo)
    {
        ctx->philo[i].pid = fork();
        if (ctx->philo[i].pid == -1)
            return ;
        if (ctx->philo[i].pid == 0)
            ft_func_philo(&ctx->philo[i]);
    }
}
