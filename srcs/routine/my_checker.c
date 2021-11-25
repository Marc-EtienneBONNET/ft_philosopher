/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:40:07 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/25 17:07:29 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	my_died_shot(t_philo *philo, int alive)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->check_alive);
	philo->alive = alive;
	pthread_mutex_unlock(&philo->check_alive);
	while (i < philo->info->nb_philo)
	{
		pthread_mutex_lock(&philo->info->philos[i].check_alive);
		if (philo->info->philos[i].alive > 0)
			philo->info->philos[i].alive = -3;
		pthread_mutex_unlock(&philo->info->philos[i].check_alive);
		i++;
	}
}

int	check_time_last_eat(t_info *info)
{
	long long int	time_last_eat;
	int				i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_lock(&(info->philos[i].check_last_eat));
		time_last_eat = info->philos[i].time_last_eat;
		pthread_mutex_unlock(&(info->philos[i].check_last_eat));
		if ((get_time() - time_last_eat) > info->time_die)
		{
			my_died_shot(&info->philos[i], -1);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	check_philo_alive(t_philo *philo)
{
	int	philo_alive;

	pthread_mutex_lock(&philo->check_alive);
	philo_alive = philo->alive;
	pthread_mutex_unlock(&philo->check_alive);
	if (philo_alive < 0)
		return (-1);
	else
		return (1);
}
