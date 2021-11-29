/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:50:41 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/29 11:01:04 by mbonnet          ###   ########.fr       */
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
	int				nb_eat;
	unsigned long	time_starte;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	unsigned long	time_die;
	struct s_philo	*philos;
	pthread_t		god;
	pthread_mutex_t	*forks;
	pthread_mutex_t	check_write;
	pthread_mutex_t	check_alive;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				alive;
	int				nb_eat;
	unsigned long	time_last_eat;
	pthread_t		th;
	t_info			*info;
	pthread_mutex_t	check_nb_eat;
	pthread_mutex_t	check_last_eat;
	pthread_mutex_t	check_alive;
}	t_philo;

t_info			my_parse(int ac, char **av);
int				my_init_philo_info(t_info *info);
void			*my_routine(void *data);
int				my_write(t_philo *philo, char *str);
int				my_take_forks(t_philo *philo);
int				my_pose_forks(t_philo *philo);
unsigned long	get_time(void);
int				check_time_last_eat(t_info *info);
int				my_eat(t_philo *philo);
int				check_philo_alive(t_philo *philo);
int				my_usleep(t_philo *philo, unsigned long time);
int				my_sleep_and_think(t_philo *philo);
void			my_died_shot(t_philo *philo, int alive);
void			*my_routine_philo(void *data);
int				my_choose_who_died(t_philo *philo);
int				my_write_2(t_philo *philo, int nb);
#endif
