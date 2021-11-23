/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:57:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/23 10:09:04 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*my_routine_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (check_philo_alive(philo) != -1)
	{
		my_take_forks(philo);
		my_eat(philo);
		my_pose_forks(philo);
	}
	my_write(philo, "fin totale de ce philo\n");
	return (data);
}

void	*my_routine_golder(void *data)
{
	//int		i;
	t_philo	*philo;

	//i = 0;
	philo = (t_philo *)data;
	while (check_time_last_eat(philo) != -1)
	{
		usleep(10000);
	}
	my_write(philo, "\t\tis died temps avant de manger");
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
