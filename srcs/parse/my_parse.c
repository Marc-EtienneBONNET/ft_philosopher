/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:33:47 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/23 15:50:00 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_info	my_parse(int ac, char **av)
{
	t_info	info;
	int		i;
	int		x;

	i = 0;
	while (ac > ++i)
	{
		x = -1;
		while (av[i][++x])
		{
			if (av[i][x] > '9' || av[i][x] < '0')
			{
				info.nb_philo = -1;
				return (info);
			}
		}
	}
	info.nb_philo = atoi(av[1]);
	info.time_die = atoi(av[2]);
	info.time_eat = atoi(av[3]);
	info.time_sleep = atoi(av[4]);
	return (info);
}