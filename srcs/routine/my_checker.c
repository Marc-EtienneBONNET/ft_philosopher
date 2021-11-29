/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:40:07 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/29 17:24:01 by mbonnet          ###   ########.fr       */
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

void	my_died_shot(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->nb_philo)
	{
		pthread_mutex_lock(&philo->info->philos[i].check_alive);
		philo->info->philos[i].alive = -1;
		pthread_mutex_unlock(&philo->info->philos[i].check_alive);
		i++;
	}
	my_write(philo, "\t\tdied");
}

int	check_time_and_nb_eat(t_info *info)
{
	unsigned long	time_last_eat;
	unsigned long	big_time;
	long long int	time;
	int				i;

	big_time = 0;
	i = 0;
	while (i < info->nb_philo)
	{
		if (check_one_philo(&info->philos[i]) == -1)
			return (-1);
		pthread_mutex_lock(&(info->philos[i].check_last_eat));
		time_last_eat = info->philos[i].time_last_eat;
		pthread_mutex_unlock(&(info->philos[i].check_last_eat));
		time = get_time() - time_last_eat;
		if ((unsigned long)time > info->time_die)
		{
			my_died_shot(&info->philos[i]);
			return (-1);
		}
		if ((unsigned long)time > big_time)
			big_time = time;
		i++;
	}
	time = info->time_die - big_time;
	return (time);
}

int	check_all_philo(t_philo *philo)
{
	int	alive;

	pthread_mutex_lock(&philo->info->check_alive);
	alive = philo->info->alive;
	pthread_mutex_unlock(&philo->info->check_alive);
	return (alive);
}

int	check_one_philo(t_philo *philo)
{
	int	philo_alive;

	pthread_mutex_lock(&philo->check_alive);
	philo_alive = philo->alive;
	pthread_mutex_unlock(&philo->check_alive);
	return (philo_alive);
}
