/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:57:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/24 16:21:22 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*my_write_died(t_philo *philo)
{
	int	alive;
	int	nb_eat;

	pthread_mutex_lock(&philo->check_alive);
	alive = philo->alive;
	pthread_mutex_unlock(&philo->check_alive);
	if (alive == -1)
	{
		pthread_mutex_lock(&philo->check_nb_eat);
		nb_eat = philo->nb_eat;
		pthread_mutex_unlock(&philo->check_nb_eat);
		if (philo->info->nb_eat != -1 && nb_eat >= philo->info->nb_eat)
			return (NULL);
		else
			my_write(philo, "died");
	}
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
		if (eat == -1 || eat == -2 || eat == -3 || my_pose_forks(philo) == -1)
		{
			if (eat != -2 && eat != -3)
			{
				return (my_write_died(philo));
			}
		}
		if (my_sleep_and_think(philo) == -1)
		{
			return (my_write_died(philo));
		}
	}
	return (my_write_died(philo));
}
