/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:45:41 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/15 17:47:14 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	my_init_mutex(t_element **element)
{
	pthread_mutex_init(&((*element)->check_write), NULL);
	pthread_mutex_init(&((*element)->check_alive), NULL);
	pthread_mutex_init(&((*element)->check_time_eat), NULL);
	pthread_mutex_init(&((*element)->check_time_sleep), NULL);
	pthread_mutex_init(&((*element)->check_time_start), NULL);
}

t_element	*my_create_element(t_element parsage)
{
	t_element	*element;
	int			i;

	i = 0;
	element = malloc(sizeof(t_element));
	if (!element)
		return (NULL);
	element->philos = malloc(sizeof(t_philo) * (parsage.nb_philo));
	if (!element->philos)
		return (NULL);
	element->alive = parsage.alive;
	element->nb_philo = parsage.nb_philo;
	element->time_start = parsage.time_start;
	element->time_die = parsage.time_die;
	element->time_eat = parsage.time_eat;
	element->time_sleep = parsage.time_sleep;
	element->nb_repas = parsage.nb_repas;
	while (i < parsage.nb_philo)
		element->philos[i++].element = element;
	my_init_mutex(&element);
	return (element);
}
