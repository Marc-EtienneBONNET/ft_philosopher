/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:57:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/23 11:54:34 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*my_routine_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (check_philo_alive(philo) != -1)
	{
		if (my_take_forks(philo) == -1)
		{
			my_write(philo, "\t\tsorti processe");
			return (data);
		}
		if (my_eat(philo) == -1 || my_pose_forks(philo) == -1)
			return (data);
	}
	my_write(philo, "\t\tsorti processe");
	return (data);
}

void	*my_routine_golder(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (check_philo_alive(philo) != -1)
	{
		if (check_time_last_eat(philo) == -1)
			break;
		usleep(1000);
	}
	my_write_alive(philo);
	my_write(philo, "\tarret du processe gold a cause d un mort");
	return (data);
}

void	*my_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_create(&(philo->gold), NULL, my_routine_golder, philo);
	my_routine_philo(data);
	pthread_join(philo->gold, NULL);
	return (NULL);
}
