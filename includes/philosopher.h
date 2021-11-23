/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:50:41 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/23 11:04:15 by mbonnet          ###   ########.fr       */
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
	int				alive;
	int				nb_philo;
	long long int	time_starte;
	struct s_philo	*philos;
	long long int	time_die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	check_write;
	pthread_mutex_t	check_alive;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				alive;
	long long int	time_last_eat;
	pthread_t		th;
	pthread_t		gold;
	t_info			*info;
	pthread_mutex_t	check_last_eat;
	pthread_mutex_t	check_alive;
}	t_philo;

t_info			my_parse(int ac, char **av);
int				my_init_philo_info(t_info *info);
void			*my_routine(void *data);
void			my_write(t_philo *philo, char *str);
int				check_alive(t_philo *philo);
int				my_take_forks(t_philo *philo);
int				my_pose_forks(t_philo *philo);
long long int	get_time(void);
int				check_time_last_eat(t_philo *philo);
int				my_eat(t_philo *philo);
int				check_philo_alive(t_philo *philo);
void			my_write_alive(t_philo *philo);

#endif
