/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:40:18 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/15 19:47:59 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	my_take_forks(t_philo *philo)
{
	int	index_left;
	int	index_right;

	if (check_alive(philo->element) == -1)
		return (-1);
	if (philo->id == 1)
		index_right = philo->element->nb_philo - 1;
	else
		index_right = philo->id - 1;
	index_left = philo->id;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&index_right);
		pthread_mutex_lock(&index_left);
	}
	else
	{
		pthread_mutex_lock(&index_left);
		pthread_mutex_lock(&index_right);
	}
}

void	*routine_philo(void *data)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)data;
	while (check_alive(philo->element) != -1)
	{
		if (my_take_forks(&(philo[i])) == -1)
			return (-1);
		i++;
	}
	return (NULL);
}
