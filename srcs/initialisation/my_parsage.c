/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parsage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:53:29 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/15 17:22:44 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	my_controle_format_arg(int ac, char **av)
{
	int	i;
	int	x;

	i = 0;
	while (++i < ac)
	{
		x = -1;
		while (av[i][++x] != '\0')
			if (av[i][x] < '0' || av[i][x] > 9)
				return (-1);
	}
	return (1);
}

t_element	si_echec()
{
	t_element	tmp;

	tmp.time_sleep = -1;
	tmp.time_eat = -1;
	tmp.time_die = -1;
	tmp.nb_philo = -1;
	tmp.alive = -1;
	tmp.time_start = -1;
	tmp.nb_philo = -1;
	return (tmp);
}

t_element	my_parsage(int ac, char **av, t_element tmp)
{
	if ((ac != 5 && ac != 6) || my_controle_format_arg(ac, av) == -1)
	{
		tmp = si_echec();
		return (tmp);
	}
	else if (ac == 6)
		tmp.nb_repas = ft_atoi(av[5]);
	else
		tmp.nb_repas = -1;
	tmp.time_sleep = (long long int)ft_atoi(av[4]);
	tmp.time_eat = (long long int)ft_atoi(av[3]);
	tmp.time_die = (long long int)ft_atoi(av[2]);
	tmp.time_start = get_time();
	tmp.nb_philo = (long long int)ft_atoi(av[1]);
	tmp.alive = 1;
	return (tmp);
}
