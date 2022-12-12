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

#include "structs_bonus.h"
#include "philo_bonus.h"
#include "utils_bonus.h"

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
	ctx = ft_parse(argv);
	ft_create_thread(ctx);
	ft_death(&ctx);
	ft_join_thread(ctx);
	ft_free(ctx);
	return (EXIT_SUCCESS);
}
