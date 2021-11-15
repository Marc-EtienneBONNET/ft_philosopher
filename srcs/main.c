/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:58:32 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/15 17:52:38 by mbonnet          ###   ########.fr       */
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

void	my_check_philo_alive(t_element *element)
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
	int			i;

	element = (t_element *)data;
	i = 0;
	while (element->alive == 1)
	{
		my_check_philo_alive(element);
		usleep(100);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_element	*element;
	t_element	tmp;

	tmp = my_parsage(ac, av, tmp);
	if (tmp.nb_philo == -1)
		return (-1);
	element = my_create_element(tmp);
	(void)element;
	pthread_create(&(element->gold), NULL, my_routine_golder, element);
	// a partire d ici, il n y a plus quinisialiser les processe des philosof et cr2er leur routine 
	return (0);
}
