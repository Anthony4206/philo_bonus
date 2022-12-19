/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:23:49 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/12 09:56:01 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>

#include "structs_bonus.h"
#include "philo_bonus.h"
#include "utils_bonus.h"

void    ft_wait(t_ctx ctx)
{
    int i;
    int ret;

    i = -1;
    while (++i < ctx.nb_philo)
    {
        waitpid(-1, &ret, 0);
        if (ret)
        {
            i = -1;
            while (++i < ctx.nb_philo)
                kill(ctx.philo[i].pid, SIGTERM);
            break ;
        }
    }
}

void    ft_sem_finish(t_ctx ctx)
{
    sem_close(ctx.sem.forks);
	sem_close(ctx.sem.print);
	sem_close(ctx.sem.checker);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/checker");
}

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc < 5 || argc > 6 || ft_error(argv))
	{
		ft_putstr_fd("syntax error: number_of_philosophers ", 2);
		ft_putstr_fd("time_to_die time_to_eat time_to_sleep ", 2);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
		return (EXIT_FAILURE);
	}
	if (ft_strlen(argv[1]) == 1 && argv[1][0] == '1')
	{
		usleep(ft_atoi(argv[2]) * 1000);
		ft_putstr_fd(argv[2], 2);
		ft_putstr_fd(" 1 died\n", 2);
		return (EXIT_SUCCESS);
	}
	if (ft_strlen(argv[5]) == 1 && argv[5][0] == '0')
		return (EXIT_SUCCESS);
	ctx = ft_parse(argv);
    ft_process_launcher(&ctx);
    ft_wait(ctx);
    ft_sem_finish(ctx);
	ft_free(ctx);
	return (EXIT_SUCCESS);
}
