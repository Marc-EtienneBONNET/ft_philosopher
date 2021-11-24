/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:57:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/24 15:41:44 by mbonnet          ###   ########.fr       */
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
	int		eat;

	philo = (t_philo *)data;
	while (check_philo_alive(philo) != -1)
	{
		if (my_take_forks(philo) == -1)
			return (my_write_died(philo));
		eat = my_eat(philo);
		if (eat == -1 || eat == -2 || my_pose_forks(philo) == -1)
		{
			if (eat != -2)
				return (my_write_died(philo));
		}
		if (my_sleep_and_think(philo) == -1)
		{
			return (my_write_died(philo));
		}
	}
	return (my_write_died(philo));
}
