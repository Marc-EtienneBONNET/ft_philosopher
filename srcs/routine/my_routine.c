/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:57:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/29 17:57:40 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	my_write_3(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->check_write);
	printf("%ld\t%d\t%s\n", get_time()
		- philo->info->time_starte, philo->id + 1, str);
	pthread_mutex_unlock(&philo->info->check_write);
	return (1);
}

void	*my_routine_philo(void *data)
{
	int		one_philo;
	t_philo	*philo;

	philo = (t_philo *)data;
	while (one_philo != -1)
	{
		one_philo = check_one_philo(philo);
		if (my_take_forks(philo) == -1)
			return (NULL);
		if (my_eat(philo) == -1)
			return (NULL);
		if (my_pose_forks(philo) == -1)
			return (NULL);
		if (my_sleep_and_think(philo) == -1)
			return (NULL);
	}
	return (NULL);
}
