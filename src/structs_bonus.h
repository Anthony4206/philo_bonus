/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:26:01 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/12 11:40:31 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# include <pthread.h>
# include <semaphore.h>

struct	s_ctx;

typedef struct s_philos
{
	int				philo;
	long int		*last_diner;
	long int		start;
	struct s_ctx	*rules;
}					t_philos;

typedef struct s_thread
{
	pthread_t	*th;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*is_die;
}				t_thread;

typedef struct s_ctx
{
	int			nb_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			nb_diner;
	long int	start;
	pid_t		*pid;
	t_thread	ths;
	t_philos	*philo;
}				t_ctx;

#endif
