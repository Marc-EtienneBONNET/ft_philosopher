/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:40:07 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/26 10:34:53 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	my_write_2(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->info->check_write);
	printf("Each philos eat %d time(s)\n", nb);
	pthread_mutex_unlock(&philo->info->check_write);
	return (1);
}

void	my_died_shot(t_philo *philo, int alive)
{
	int	i;

	pthread_mutex_lock(&philo->info->check_alive);
	i = philo->info->alive;
	philo->info->alive = -1;
	pthread_mutex_unlock(&philo->info->check_alive);
	pthread_mutex_lock(&philo->check_alive);
	philo->alive = alive;
	pthread_mutex_unlock(&philo->check_alive);
	if (alive == -1 && i != -1)
		my_write(philo, "died");
}

int	check_time_last_eat(t_info *info)
{
	long long int	time_last_eat;
	int				i;
	long long int	big_time;
	long long int	time;

	i = 0;
	big_time = 0;
	while (i < info->nb_philo)
	{
		if (check_philo_alive(&info->philos[i]) == -1)
			return (-1);
		pthread_mutex_lock(&(info->philos[i].check_last_eat));
		time_last_eat = info->philos[i].time_last_eat;
		pthread_mutex_unlock(&(info->philos[i].check_last_eat));
		time = get_time() - time_last_eat;
		if (time > info->time_die)
		{
			my_died_shot(&info->philos[i], -1);
			return (-1);
		}
		if (time > big_time)
			big_time = time;
		i++;
	}
	return (time);
}

int	check_philo_alive(t_philo *philo)
{
	int	philo_alive;
	int	alive;

	pthread_mutex_lock(&philo->info->check_alive);
	alive = philo->info->alive;
	pthread_mutex_unlock(&philo->info->check_alive);
	pthread_mutex_lock(&philo->check_alive);
	philo_alive = philo->alive;
	pthread_mutex_unlock(&philo->check_alive);
	if (philo_alive < 0 || alive < 0)
		return (-1);
	else
		return (1);
}
