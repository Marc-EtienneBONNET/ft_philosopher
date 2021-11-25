/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:57:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/25 21:41:14 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*my_write_died(t_philo *philo)
{
	int	alive;

	pthread_mutex_lock(&philo->check_alive);
	alive = philo->alive;
	pthread_mutex_unlock(&philo->check_alive);
	if (alive == -1)
		my_write(philo, "died");
	return (NULL);
}

void	*my_routine_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (check_philo_alive(philo) != -1)
	{
		if (my_take_forks(philo) == -1)
		{
			my_write(philo, "\t\tici");
			return (my_write_died(philo));
		}
		if (my_eat(philo) == -1)
		{
			my_write(philo, "\t\tici");
			return (my_write_died(philo));
		}
		if (my_pose_forks(philo) == -1)
			return (my_write_died(philo));
		if (my_sleep_and_think(philo) == -1)
		{
			my_write(philo, "\t\tici");
			return (my_write_died(philo));
		}
	}
	my_write(philo, "\t\tici");
	return (my_write_died(philo));
}
