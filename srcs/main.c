/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:58:32 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/15 19:28:15 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_element	*element;
	t_element	tmp;
	int			i;

	i = -1;
	tmp = my_parsage(ac, av, tmp);
	if (tmp.nb_philo == -1)
		return (-1);
	element = my_create_element(tmp);
	(void)element;
	pthread_create(&(element->gold), NULL, my_routine_golder, element);
	while (++i < element->nb_philo)
		pthread_mutex_init(&(element->forks[i]), NULL);
	i = -1;
	while (++i < element->nb_philo)
		pthread_create(&(element->philos[i].th), NULL, routine_philo, element);
	// a partire d ici, il n y a plus quinisialiser les processe des philosof et cr2er leur routine 
	return (0);
}
