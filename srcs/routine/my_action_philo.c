/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_action_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:40:07 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/23 11:56:20 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	my_fork_write(t_philo *philo, int index)
{
	pthread_mutex_lock(&philo->info->check_write);
	printf("%lld\tid : %d\t take fork number : %d\n", get_time() - philo->info->time_starte, philo->id, index);
	pthread_mutex_unlock(&philo->info->check_write);
}

void	ft_take_one_forks(int index, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[index]);
	my_fork_write(philo, index);
}

int	my_take_forks(t_philo *philo)
{
	int	index_left;
	int	index_right;

	if (check_philo_alive(philo) == -1)
		return (-1);
	index_left = philo->id;
	index_right = philo->id + 1;
	if (philo->id == philo->info->nb_philo - 1)
		index_right = 0;
	if (philo->id % 2 == 0)
	{
		ft_take_one_forks(index_right, philo);
		ft_take_one_forks(index_left, philo);
	}
	else
	{
		ft_take_one_forks(index_left, philo);
		ft_take_one_forks(index_right, philo);
	}
	return (1);
}

int	my_pose_forks(t_philo *philo)
{
	int	index_left;
	int	index_right;

	index_left = philo->id;
	index_right = philo->id + 1;
	if (philo->id == philo->info->nb_philo - 1)
		index_right = 0;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->info->forks[index_right]);
		pthread_mutex_unlock(&philo->info->forks[index_left]);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->forks[index_left]);
		pthread_mutex_unlock(&philo->info->forks[index_right]);
	}
	my_write(philo, "fourchettes posees");
	return (1);
}







int	my_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->check_last_eat);
	my_write(philo, "is eating");
	philo->time_last_eat = get_time();
	pthread_mutex_unlock(&philo->check_last_eat);
	usleep(100000);
	//quand j aurais fais mon propre usleep, il faudra bien qu en cas d erreur il libere les deux fourchette !!
	return (1);
}

int	check_philo_alive(t_philo *philo)
{
	int	philo_alive;
	int	other_philo_alive;

	pthread_mutex_lock(&philo->check_alive);
	philo_alive = philo->alive;
	pthread_mutex_unlock(&philo->check_alive);
	pthread_mutex_lock(&philo->info->check_alive);
	other_philo_alive = philo->info->alive;
	pthread_mutex_unlock(&philo->info->check_alive);
	if (philo_alive == -1)
	{
		my_write(philo, "\t\tcheck_alive renvoi -1 morth de ce philo");
		return (-1);
	}
	else if (other_philo_alive == -1)
	{
		my_write(philo, "\tcheck_alive renvoi -1 morth d un des philo");
		return (-1);
	}
	return (1);
}
