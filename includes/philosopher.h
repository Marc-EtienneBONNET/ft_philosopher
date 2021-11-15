/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:50:41 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/15 19:31:35 by mbonnet          ###   ########.fr       */
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

typedef struct s_philo
{
	int					id;
	long long int		time_last_eat;
	pthread_mutex_t		check_last_eat;
	long long int		nb_repas;
	pthread_mutex_t		check_nb_repas;
	struct s_element	*element;
	pthread_t			th;
}	t_philo;

typedef struct s_element
{
	int				alive;
	int				nb_philo;
	long long int	time_start;
	long long int	time_die;
	long long int	time_eat;
	long long int	time_sleep;
	int				nb_repas;
	t_philo			*philos;
	pthread_mutex_t	check_write;
	pthread_mutex_t	check_alive;
	pthread_mutex_t	*forks;
	pthread_t		gold;
}	t_element;

long long int	get_time(void);
t_element		*my_create_element(t_element tmp);
t_element		my_parsage(int ac, char **av, t_element tmp);
void			*my_routine_golder(void *data);
void			*routine_philo(void *data);
int				check_alive(t_element *element);

#endif
