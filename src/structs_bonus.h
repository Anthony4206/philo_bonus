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
	int				philo_id;
	long int		*last_diner;
	int			    nb_diner;
	long int		start;
    int             is_die;
    pid_t           pid;
	pthread_t	    th;
	struct s_ctx	*rules;
}					t_philos;

typedef struct s_sem
{
	sem_t		*forks;
	sem_t		*print;
	sem_t		*checker;
}				t_sem;

typedef struct s_ctx
{
	int			nb_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			nb_diner;
    int         is_die;
	long int	start;
	t_sem	    sem;
	t_philos	*philo;
}				t_ctx;

#endif
