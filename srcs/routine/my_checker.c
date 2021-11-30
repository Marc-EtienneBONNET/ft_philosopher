/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:40:07 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/30 11:14:58 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

void	ft_global_over_dose(t_philo *philo)
{
	int	i;

	i = 0;
	//printf("%ld j arrive ici !\n", get_time() - philo->info->time_starte);
	while (i < philo->info->nb_philo)
	{
		pthread_mutex_lock(&philo->info->philos[i].check_alive);
		philo->info->philos[i].alive = -2;
		pthread_mutex_unlock(&philo->info->philos[i].check_alive);
		i++;
	}
	my_write(philo, "\t\tEach philo have eat enought");
}

int	check_nb_eat(t_philo *philo)
{
	int	nb_eat;

	if (philo->info->nb_eat == -1)
		return (1);
	//printf("%ld je passe ici  !\n", get_time() - philo->info->time_starte);
	pthread_mutex_lock(&philo->check_nb_eat);
	nb_eat = philo->nb_eat;
	pthread_mutex_unlock(&philo->check_nb_eat);
	if (nb_eat >= philo->info->nb_eat)
		return (-1);
	return (1);
}

int	check_time_and_nb_eat(t_info *info)
{
	unsigned long	time_last_eat;
	unsigned long	big_time;
	long long int	time;
	int				i;
	int				all_over_dose;

	big_time = 0;
	i = 0;
	all_over_dose = 0;
	while (i < info->nb_philo)
	{
		if (check_one_philo(&info->philos[i]) == -1)
			return (-1);
		if (check_nb_eat(&info->philos[i]) == -1)
			all_over_dose++;
		if (all_over_dose == info->nb_philo)
		{
			ft_global_over_dose(&info->philos[i]);
			return (-1);
		}
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
	if (philo_alive < 0)
		return (-1);
	return (1);
}
