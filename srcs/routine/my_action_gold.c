/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_action_gold.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:40:07 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/23 18:30:32 by mbonnet          ###   ########.fr       */
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

int	check_time_last_eat(t_philo *philo)
{
	long long int	time_last_eat;

	pthread_mutex_lock(&philo->check_last_eat);
	time_last_eat = philo->time_last_eat;
	pthread_mutex_unlock(&philo->check_last_eat);
	if ((get_time() - time_last_eat) > philo->info->time_die)
	{
		return (-1);
	}
	return (1);
}

int	check_nb_eat(t_philo *philo)
{
	long long int	nb_eat;

	if (philo->info->nb_eat == -1)
		return (1);
	pthread_mutex_lock(&philo->check_nb_eat);
	nb_eat = philo->nb_eat;
	pthread_mutex_unlock(&philo->check_nb_eat);
	if (nb_eat >= philo->info->nb_eat)
	{
		my_write(philo,"\t\ta assez manger");
		return (-1);
	}
	return (1);
}
