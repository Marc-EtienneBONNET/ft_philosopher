/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:01:08 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/30 15:02:26 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	my_write(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->check_write);
	if (str[0] == 'd' || str[0] == '\t' || check_one_philo(philo) == 1)
		printf("%ld\t%d\t%s\n", get_time()
			- philo->info->time_starte, philo->id + 1, str);
	pthread_mutex_unlock(&philo->info->check_write);
	return (1);
}

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

int	my_usleep(t_philo *philo, unsigned long time)
{
	unsigned long	fin;

	fin = get_time() + time;
	(void)philo;
	while (fin > get_time())
	{
		usleep(10);
		if (check_one_philo(philo) == -1)
			return (-1);
	}
	return (1);
}

int	my_usleep_2(unsigned long time)
{
	unsigned long	fin;

	fin = get_time() + time;
	while (fin > get_time())
	{
		usleep(10);
	}
	return (1);
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
