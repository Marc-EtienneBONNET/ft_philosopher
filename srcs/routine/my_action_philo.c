/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_action_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:40:07 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/24 11:10:31 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_take_one_forks(int index, t_philo *philo)
{
	if (check_philo_alive(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->info->forks[index]);
	if (check_philo_alive(philo) == -1)
	{
		pthread_mutex_unlock(&philo->info->forks[index]);
		return (-1);
	}
	my_write(philo, "take a fork");
	return (1);
}

int	my_take_forks(t_philo *philo)
{
	int	index_left;
	int	index_right;

	if (check_philo_alive(philo) == -1)
		return (-1);
	index_left = philo->id;
	index_right = philo->id + 1;
	if (philo->id == philo->info->nb_philo - 1)
		index_right = 0;
	if (philo->id % 2 == 0)
	{
		if (ft_take_one_forks(index_right, philo) == -1)
			return (-1);
		else
		{
			if (ft_take_one_forks(index_left, philo) == -1)
			{
				pthread_mutex_unlock(&philo->info->forks[index_right]);
				return (-1);
			}
		}
	}
	else
	{
		if (ft_take_one_forks(index_left, philo) == -1)
			return (-1);
		else
		{
			if (ft_take_one_forks(index_right, philo) == -1)
			{
				pthread_mutex_unlock(&philo->info->forks[index_left]);
				return (-1);
			}
		}
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

int	my_eat(t_philo *philo)
{
	int	checker_nb_repas;
	int	other_philo_alive;

	if (check_philo_alive(philo) == -1)
	{
		my_pose_forks(philo);
		return (-1);
	}
	my_write(philo, "is eating");
	pthread_mutex_lock(&philo->check_last_eat);
	philo->time_last_eat = get_time();
	pthread_mutex_unlock(&philo->check_last_eat);
	pthread_mutex_lock(&philo->check_nb_eat);
	philo->nb_eat++;
	checker_nb_repas = philo->nb_eat;
	pthread_mutex_unlock(&philo->check_nb_eat);
	if (philo->info->nb_eat != -1 && checker_nb_repas >= philo->info->nb_eat)
	{
		pthread_mutex_lock(&philo->info->check_alive);
		other_philo_alive = philo->info->alive;
		pthread_mutex_unlock(&philo->info->check_alive);
		if (other_philo_alive == -1)
			return (-2);
		my_died_shot(philo);
		return (-1);
	}
	else if (my_usleep(philo, philo->info->time_eat) == -1)
	{
		my_pose_forks(philo);
		return (-1);
	}
	return (1);
}


int	my_sleep_and_think(t_philo *philo)
{
	my_write(philo, "is sleeping");
	if (my_usleep(philo, philo->info->time_sleep) == -1)
		return (-1);
	my_write(philo, "is thinking");
	return (1);
}
