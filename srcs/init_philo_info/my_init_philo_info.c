/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init_philo_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:46:00 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/23 18:13:14 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		my_init_philo_info(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->check_write, NULL);
	pthread_mutex_init(&info->check_alive, NULL);
	info->alive = 1;
	info->philos = malloc(sizeof(t_philo) * info->nb_philo);
	info->time_starte = get_time();
	info->forks = malloc(sizeof(t_philo) * info->nb_philo);
	while (i < info->nb_philo)
	{
		info->philos[i].id = i;
		info->philos[i].alive = 1;
		info->philos[i].info = info;
		info->philos[i].nb_eat = 0;
		info->philos[i].time_last_eat = info->time_starte;
		pthread_mutex_init(&(info->philos[i].check_nb_eat), NULL);
		pthread_mutex_init(&(info->philos[i].check_alive), NULL);
		pthread_mutex_init(&(info->philos[i].check_last_eat), NULL);
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
		pthread_mutex_init(&(info->forks[i++]), NULL);
	return (0);
}
