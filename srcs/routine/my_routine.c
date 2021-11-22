/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:57:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/22 18:57:45 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*my_routine_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (check_alive(philo) != -1)
	{
		my_take_forks(philo);
		my_pose_forks(philo);
		usleep(100000);
	}
	my_write(philo->info, "is died", philo->id);
	return (data);
}

void	*my_routine_golder(void *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)data;
	while (i >= 0)
	{
		if (i == 10)
		{
			my_write(philo->info, "god",philo->id);
			pthread_mutex_lock(&philo->check_alive);
			philo->alive = -1;
			pthread_mutex_unlock(&philo->check_alive);
			return (NULL);
		}
		usleep(99999);
		i++;
	}
	return (data);
}

void	*my_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_create(&(philo->gold), NULL, my_routine_golder, philo);
	my_routine_philo(data);
	pthread_join(philo->gold, NULL);
	return (data);
}
