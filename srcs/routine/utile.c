/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:01:08 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/22 18:22:32 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	my_write(t_info *info, char *str, int id)
{
	pthread_mutex_lock(&info->check_write);
	printf("(%s),\tid : %d\n", str, id);
	pthread_mutex_unlock(&info->check_write);
}

int	check_alive(t_philo *philo)
{
	int	alive;

	pthread_mutex_lock(&philo->check_alive);
	alive = philo->alive;
	pthread_mutex_unlock(&philo->check_alive);
	return (alive);
}
