/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init_philo_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:46:00 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/22 18:54:58 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		my_init_philo_info(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->check_write, NULL);
	info->philos = malloc(sizeof(t_philo) * info->nb_philo);
	info->forks = malloc(sizeof(t_philo) * info->nb_philo);
	while (i < info->nb_philo)
	{
		info->philos[i].id = i;
		info->philos[i].alive = 1;
		info->philos[i].info = info;
		pthread_mutex_init(&(info->philos[i].check_alive), NULL);
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
		pthread_mutex_init(&(info->forks[i++]), NULL);
	return (0);
}
