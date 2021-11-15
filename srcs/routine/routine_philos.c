/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:40:18 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/15 20:44:08 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	take_one_fork(t_philo *philo, int index)
{
	if (check_alive(philo->element) == -1)
		return (-1);
	pthread_mutex_lock(&philo->element->forks[index]);
	return (my_write(philo->element, *philo, "has taken a fork", 1));
	
}

int	my_take_forks_2(t_philo *philo, int index_right, int index_left)
{
	if (philo->id % 2 == 0)
	{
		if (take_one_fork(philo, index_right) == -1)
			return (-1);
		if (take_one_fork(philo, index_left) == -1)
		{
			pthread_mutex_unlock(&philo->element->forks[index_right]);
			return (-1);
		}
	}
	else
	{
		if (take_one_fork(philo, index_left) == -1)
			return (-1);
		if (take_one_fork(philo, index_right) == -1)
		{
			pthread_mutex_unlock(&philo->element->forks[index_left]);
			return (-1);
		}
	}
	return (1);
}

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
	return (my_take_forks_2(philo, index_right, index_left));
}

void	*routine_philo(void *data)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)data;
	while (check_alive(philo->element) != -1)
	{
		if (my_take_forks(&(philo[i])) == -1)
			return (NULL);
		i++;
	}
	return (NULL);
}
