/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:45:41 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/15 19:19:37 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	my_init_mutex(t_element **element)
{
	pthread_mutex_init(&((*element)->check_write), NULL);
	pthread_mutex_init(&((*element)->check_alive), NULL);
}

void	my_create_philo(t_element **element)
{
	int	i;

	i = 0;
	while (i < (*element)->nb_philo)
	{
		(*element)->philos[i].id = i + 1;
		(*element)->philos[i].time_last_eat = (*element)->time_start;
		(*element)->philos[i].nb_repas = 0;
		(*element)->philos[i].element = *element;
		pthread_mutex_init(&(*element)->philos[i].check_last_eat, NULL);
		pthread_mutex_init(&(*element)->philos[i].check_nb_repas, NULL);
		i++;
	}
}

t_element	*my_create_element(t_element parsage)
{
	t_element	*element;

	element = malloc(sizeof(t_element));
	if (!element)
		return (NULL);
	element->philos = malloc(sizeof(t_philo) * (parsage.nb_philo));
	if (!element->philos)
	{
		free(element);
		return (NULL);
	}
	element->alive = parsage.alive;
	element->nb_philo = parsage.nb_philo;
	element->time_start = parsage.time_start;
	element->time_die = parsage.time_die;
	element->time_eat = parsage.time_eat;
	element->time_sleep = parsage.time_sleep;
	element->nb_repas = parsage.nb_repas;
	my_create_philo(&element);
	my_init_mutex(&element);
	return (element);
}
