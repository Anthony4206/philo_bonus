/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:25:08 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/12 11:33:36 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "structs_bonus.h"

t_sem	    ft_init_sem(t_ctx ctx);
t_philos	*ft_init_philo(t_ctx *ctx);
t_ctx		ft_parse(char **argv);
void	    ft_process_launcher(t_ctx *ctx);
void	    *ft_death(void *philo);
void		ft_free(t_ctx ctx);

#endif
