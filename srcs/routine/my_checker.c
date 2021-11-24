/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:40:07 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/24 16:09:44 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	my_died_shot(t_philo *philo)
{
	pthread_mutex_lock(&philo->check_alive);
	philo->alive = -1;
	pthread_mutex_unlock(&philo->check_alive);
	pthread_mutex_lock(&philo->info->check_alive);
	philo->info->alive = -1;
	pthread_mutex_unlock(&philo->info->check_alive);
}

void	my_died_shot_2(t_philo *philo)
{
	pthread_mutex_lock(&philo->check_alive);
	philo->alive = -1;
	pthread_mutex_unlock(&philo->check_alive);
}

int	my_choose_who_died(t_philo *philo)
{
	int	other_philo_alive;

	pthread_mutex_lock(&philo->info->check_alive);
	other_philo_alive = philo->info->alive;
	pthread_mutex_unlock(&philo->info->check_alive);
	if (other_philo_alive == -1)
		return (-2);
	my_died_shot(philo);
	return (-3);
}

int	check_time_last_eat(t_philo *philo)
{
	long long int	time_last_eat;

	pthread_mutex_lock(&philo->check_last_eat);
	time_last_eat = philo->time_last_eat;
	pthread_mutex_unlock(&philo->check_last_eat);
	if ((get_time() - time_last_eat) > philo->info->time_die)
		return (-1);
	return (1);
}

int	check_philo_alive(t_philo *philo)
{
	int	other_philo_alive;

	pthread_mutex_lock(&philo->info->check_alive);
	other_philo_alive = philo->info->alive;
	pthread_mutex_unlock(&philo->info->check_alive);
	if (other_philo_alive == -1)
		return (-1);
	else
	{
		if (check_time_last_eat(philo) == -1)
			return (-1);
	}
	return (1);
}
