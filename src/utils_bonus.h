/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:29:34 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/12 09:56:34 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "sys/time.h"

# include "structs_bonus.h"

int			ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
void		*ft_calloc(size_t count, size_t size);
int			ft_atoi(const char *str);
int			ft_error(char **argv);
void		ft_usleep(t_ctx *rules, long time);
long int	ft_diff(struct timeval diff);
long int	ft_death_diff(long int now, long int last);
long int	ft_time(long int start);
void		ft_lock_print(t_ctx *rules, int philo, char *msg);

#endif