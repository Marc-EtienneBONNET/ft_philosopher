/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:57:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/30 15:52:12 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	my_write_2(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->check_write);
	if (str[0] == 'd' || str[0] == '\t' || check_one_philo(philo) == 1)
		printf("%ld %s\n", get_time()
			- philo->info->time_starte, str);
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
			break ;
		if (my_eat(philo) == -1)
			break ;
		if (my_pose_forks(philo) == -1)
			break ;
		if (my_sleep_and_think(philo) == -1)
			break ;
	}
	return (NULL);
}
