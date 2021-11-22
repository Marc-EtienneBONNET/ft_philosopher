/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:50:41 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/22 18:45:53 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include "libft.h"

typedef struct s_info
{
	int				nb_philo;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	check_write;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				alive;
	pthread_t		th;
	pthread_t		gold;
	t_info			*info;
	pthread_mutex_t	check_alive;
}	t_philo;

t_info	my_parse(int ac, char **av);
int		my_init_philo_info(t_info *info);
void	*my_routine(void *data);
void	my_write(t_info *info, char *str, int id);
int		check_alive(t_philo *philo);
int		my_take_forks(t_philo *philo);
int		my_pose_forks(t_philo *philo);

#endif
