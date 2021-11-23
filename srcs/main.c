/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:58:32 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/23 08:58:23 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_info	info;
	int		i;

	i = 0;
	info = my_parse(ac, av);
	if (info.nb_philo == -1)
		return (-1);
	my_init_philo_info(&info);
	while (info.nb_philo > i)
	{
		pthread_create(&(info.philos[i].th), NULL, my_routine, &info.philos[i]);
		i++;
	}
	i = 0;
	while (info.nb_philo > i)
	{
		pthread_join(info.philos[i].th, NULL);
		i++;
	}
	return (0);
}
