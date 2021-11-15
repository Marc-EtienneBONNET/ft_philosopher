/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:04:40 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/15 19:31:51 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long int	get_time(void)
{
	struct timeval	tmp;
	long long int	time;

	gettimeofday(&tmp, NULL);
	time = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	return (time);
}

int	my_usleep(t_element *element, long long int time)
{
	long long int	start;
	long long int	tmp;

	start = get_time();
	while (tmp < (start + time))
	{
		tmp = get_time();
		if (check_alive(element) == -1)
			return (-1);
		usleep(500);
	}
	return (1);
}

int	my_write(t_element *element, t_philo philo, char *str)
{
	pthread_mutex_lock(&element->check_write);
	if (check_alive(element) == 1 || str[0] == 'd')
		printf("%lld\t%d\t%s\n", (get_time() - element->time_start),
			philo.id, str);
	pthread_mutex_unlock(&element->check_write);
	return (1);
}

int	check_alive(t_element *element)
{
	int	res;

	pthread_mutex_lock(&element->check_alive);
	res = element->alive;
	pthread_mutex_unlock(&element->check_alive);
	return (res);
}
