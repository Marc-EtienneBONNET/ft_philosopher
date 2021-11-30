/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:40:07 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/30 15:50:12 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	my_died_shot(t_philo *philo)
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
	my_write(philo, "died");
	return (-1);
}

int	ft_global_over_dose(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->nb_philo)
	{
		pthread_mutex_lock(&philo->info->philos[i].check_alive);
		philo->info->philos[i].alive = -2;
		pthread_mutex_unlock(&philo->info->philos[i].check_alive);
		i++;
	}
	my_write_2(philo, "\t\tEach philo have eat enought");
	return (-1);
}

int	check_nb_eat(t_philo *philo)
{
	int	nb_eat;

	if (philo->info->nb_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->check_nb_eat);
	nb_eat = philo->nb_eat;
	pthread_mutex_unlock(&philo->check_nb_eat);
	if (nb_eat >= philo->info->nb_eat)
		return (1);
	return (0);
}

long long int	take_time_last_eat(t_philo *philo)
{
	long long int	time_last_eat;

	pthread_mutex_lock(&(philo->check_last_eat));
	time_last_eat = philo->time_last_eat;
	pthread_mutex_unlock(&(philo->check_last_eat));
	return (time_last_eat);
}

int	check_time_and_nb_eat(t_info *info)
{
	unsigned long	big_time;
	long long int	time;
	int				i;
	int				all_over_dose;

	big_time = 0;
	i = -1;
	all_over_dose = 0;
	while (++i < info->nb_philo)
	{
		if (check_one_philo(&info->philos[i]) == -1)
			return (-1);
		all_over_dose += check_nb_eat(&info->philos[i]);
		if (all_over_dose == info->nb_philo)
			return (ft_global_over_dose(&info->philos[i]));
		time = get_time() - take_time_last_eat(&(info->philos[i]));
		if ((unsigned long)time > info->time_die)
			return (my_died_shot(&info->philos[i]));
		if ((unsigned long)time > big_time)
			big_time = time;
	}
	return (info->time_die - big_time);
}
