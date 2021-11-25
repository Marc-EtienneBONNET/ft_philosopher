/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:01:08 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/25 21:44:32 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	my_write(t_philo *philo, char *str)
{
	int alive;

	pthread_mutex_lock(&philo->info->check_write);
	pthread_mutex_lock(&philo->info->check_alive);
	alive = philo->info->alive;
	pthread_mutex_unlock(&philo->info->check_alive);
	if (str[0] != 'd' && (check_philo_alive(philo) == -1 || alive == -1))
	{
		pthread_mutex_unlock(&philo->info->check_write);
		return (-1);
	}
	printf("%lld\t%d\t%s\n", get_time()
		- philo->info->time_starte, philo->id + 1, str);
	pthread_mutex_unlock(&philo->info->check_write);
	return (1);
}

long long int	get_time(void)
{
	struct timeval	time;
	long long int	res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

int	my_usleep(t_philo *philo, long long int time)
{
	long long int	fin;

	fin = get_time() + time;
	(void)philo;
	while (fin > get_time())
	{
		usleep(100);
		if (check_philo_alive(philo) == -1)
			return (-1);
	}
	return (1);
}
