/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:57:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/24 10:11:09 by mbonnet          ###   ########.fr       */
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
			my_write(philo, "\t\tsorti processe take fork");
			return (NULL);
		}
		if (my_eat(philo) == -1 || my_pose_forks(philo) == -1)
		{
			my_write(philo, "\t\tsorti processe my eat");
			return (NULL);
		}
		if (my_sleep_and_think(philo) == -1)
		{
			my_write(philo, "\t\tsorti processe sleep and think");
			return (NULL);
		}
	}
	my_write(philo, "\t\tsorti processe");
	return (NULL);
}

void	*my_routine_golder(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (check_philo_alive(philo) != -1)
	{
		if (check_time_last_eat(philo) == -1)
		{
			my_died_shot(philo);
			break ;
		}
		if (check_nb_eat(philo) == -1)
		{
			my_died_shot(philo);
			break ;
		}
		usleep(50);
	}
	return (data);
}

void	*my_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_create(&(philo->gold), NULL, my_routine_golder, data);
	my_routine_philo(data);
	pthread_join(philo->gold, NULL);
	return (NULL);
}
