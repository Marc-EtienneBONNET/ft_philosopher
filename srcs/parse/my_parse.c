/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:33:47 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/24 14:53:50 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_info	my_remplis_valeur(int ac, char **av)
{
	t_info	info;

	info.nb_philo = atoi(av[1]);
	info.time_die = atoi(av[2]);
	info.time_eat = atoi(av[3]);
	info.time_sleep = atoi(av[4]);
	if (ac == 6)
		info.nb_eat = atoi(av[5]);
	else
		info.nb_eat = -1;
	return (info);
}

t_info	my_parse(int ac, char **av)
{
	int		i;
	int		x;
	t_info	info;

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
	return (my_remplis_valeur(ac, av));
}
