/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:58:32 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/24 15:14:14 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_fin_programe(t_info *info)
{
	int	i;

	i = 0;
	while (info->nb_philo > i)
	{
		pthread_join(info->philos[i].th, NULL);
		i++;
	}
	free(info->forks);
	free(info->philos);
}

int	my_init_programe(t_info *info)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (info->nb_philo > i)
	{
		if (pthread_create(&(info->philos[i].th),
				NULL, my_routine_philo, &info->philos[i]))
		{
			while (x <= i)
				pthread_join(info->philos[x++].th, NULL);
			free(info->forks);
			free(info->philos);
			printf("ERREUR : Creation des processe\n");
			return (-1);
		}
		if (i == 0)
			usleep(100);
		i++;
	}
	ft_fin_programe(info);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;

	info = my_parse(ac, av);
	if (info.nb_philo == -1)
	{
		printf("ERREUR : argument incorrecte\n");
		return (-1);
	}
	if (my_init_philo_info(&info) == -1)
	{
		printf("ERREUR : init malloc/mutexs\n");
		return (-1);
	}
	return (my_init_programe(&info));
}
