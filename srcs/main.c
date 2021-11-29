/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:58:32 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/29 17:44:42 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	my_cas_particulier(t_info *info)
{
	unsigned long	time;

	time = get_time() - info->time_starte;
	printf("%ld\t1\thas taken a fork\n", time);
	while (time <= info->time_die)
		time = get_time() - info->time_starte;
	printf("%ld\t1\tdied\n", time);
}

int	ft_ferm_programe(t_info *info, int y)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	if (i == -1)
	{
		while (x <= i)
			pthread_join(info->philos[x++].th, NULL);
		free(info->forks);
		free(info->philos);
		printf("ERREUR : Creation des processe\n");
	}
	else
	{
		pthread_join(info->god, NULL);
		while (info->nb_philo > i)
		{
			pthread_join(info->philos[i].th, NULL);
			i++;
		}
		free(info->forks);
		free(info->philos);
	}
	return (y);
}

int	my_usleep_2(unsigned long time)
{
	unsigned long	fin;

	fin = get_time() + time;
	while (fin > get_time())
	{
		usleep(10);
	}
	return (1);
}

void	*gold(void *data)
{
	t_info			*info;
	int				i;
	long long int	time;

	info = (t_info *)data;
	i = 0;
	while (i == 0)
	{
		time = check_time_and_nb_eat(info);
		if (time == -1)
			return (NULL);
		my_usleep_2(time);
	}
	return (NULL);
}

int	my_init_programe(t_info *info)
{
	int	i;

	i = 0;
	pthread_create(&(info->god), NULL, gold, info);
	while (info->nb_philo > i)
	{
		if (pthread_create(&(info->philos[i].th),
				NULL, my_routine_philo, &info->philos[i]))
			return (ft_ferm_programe(info, -1));
		if (i == 0)
			my_usleep_2(1);
		i++;
	}
	return (ft_ferm_programe(info, 0));
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
	if (info.nb_philo == 1)
	{
		my_cas_particulier(&info);
		return (0);
	}
	return (my_init_programe(&info));
}
