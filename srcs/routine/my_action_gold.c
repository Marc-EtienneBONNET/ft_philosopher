/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_action_gold.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:40:07 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/23 11:40:50 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	my_write_2(t_philo *philo, char *str, long long int temps, long long int time)
{
	pthread_mutex_lock(&philo->info->check_write);
	printf("%lld\tid : %d\t(%s)\t%lld\t max : %lld\n",get_time() - philo->info->time_starte, philo->id, str, temps, time);
	pthread_mutex_unlock(&philo->info->check_write);
}


int	check_time_last_eat(t_philo *philo)
{
	long long int	time_last_eat;

	pthread_mutex_lock(&philo->check_last_eat);
	time_last_eat = philo->time_last_eat;
	pthread_mutex_unlock(&philo->check_last_eat);
	if ((get_time() - time_last_eat) > philo->info->time_die)
	{
		pthread_mutex_lock(&philo->check_alive);
		philo->alive = -1;
		pthread_mutex_unlock(&philo->check_alive);
		pthread_mutex_lock(&philo->info->check_alive);
		philo->info->alive = -1;
		pthread_mutex_unlock(&philo->info->check_alive);
		return (-1);
	}
	return (1);
}
