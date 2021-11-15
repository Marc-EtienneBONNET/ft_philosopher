/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_gold.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:38:48 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/15 19:04:32 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_check_time(t_philo *philo)
{
	long long int	last_eat;

	pthread_mutex_lock(&philo->check_last_eat);
	last_eat = philo->time_last_eat;
	pthread_mutex_unlock(&philo->check_last_eat);
	if ((get_time() - last_eat) > philo->element->time_die)
		return (-1);
	return (1);
}

int	ft_check_nb_repat(t_philo *philo)
{
	long long int	nb_repas;

	pthread_mutex_lock(&philo->check_nb_repas);
	nb_repas = philo->nb_repas;
	pthread_mutex_unlock(&philo->check_nb_repas);
	if (philo->element->nb_repas != -1 && nb_repas >= philo->element->nb_repas)
		return (-1);
	return (1);
}

void	my_check_philos_alive(t_element *element)
{
	int	i;

	i = 0;
	while (element->nb_philo > i)
	{
		if (ft_check_time(&(element->philos[i])) == -1
			|| ft_check_nb_repat(&(element->philos[i])) == -1)
		{
			pthread_mutex_lock(&element->check_alive);
			element->alive = -1;
			pthread_mutex_unlock(&element->check_alive);
		}
		i++;
	}
}

void	*my_routine_golder(void *data)
{
	t_element	*element;

	element = (t_element *)data;
	while (element->alive == 1)
	{
		my_check_philos_alive(element);
		usleep(500);
	}
	return (NULL);
}
