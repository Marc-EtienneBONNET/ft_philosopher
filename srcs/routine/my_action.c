/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:40:07 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/22 18:49:15 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_take_one_forks(int index, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[index]);
	my_write(philo->info, "take a fork", philo->id);
}

int	my_take_forks(t_philo *philo)
{
	int	index_left;
	int	index_right;

	index_left = philo->id;
	index_right = philo->id + 1;
	if (philo->id == philo->info->nb_philo - 1)
		index_right = 0;
	if (philo->id % 2 == 0)
	{
		ft_take_one_forks(index_right, philo);
		ft_take_one_forks(index_left, philo);
	}
	else
	{
		ft_take_one_forks(index_left, philo);
		ft_take_one_forks(index_right, philo);
	}
	return (1);
}

int	my_pose_forks(t_philo *philo)
{
	int	index_left;
	int	index_right;

	index_left = philo->id;
	index_right = philo->id + 1;
	if (philo->id == philo->info->nb_philo - 1)
		index_right = 0;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->info->forks[index_right]);
		pthread_mutex_unlock(&philo->info->forks[index_left]);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->forks[index_left]);
		pthread_mutex_unlock(&philo->info->forks[index_right]);
	}
	return (1);
}
