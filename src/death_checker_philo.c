/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:23:55 by agtshiba          #+#    #+#             */
/*   Updated: 2024/10/03 17:14:32 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	look_for_death(t_table *table)
{
	long long	curr_t;
	long long	t_last_meal;
	int			i;

	i = -1;
	while (++i < table->nb_philo)
	{
		pthread_mutex_lock(&(table->meal_check));
		t_last_meal = curr_t - table->philoso[i].time_of_last_meal;
		pthread_mutex_unlock(&(table->meal_check));
		curr_t = gettimestamp(table);
		if (t_last_meal > table->time_to_die)
		{
			action_print(table, table->philoso[i].id, " is dead 💀 \n");
			pthread_mutex_lock(&(table->meal_check));
			table->smbd_has_died = 1;
			pthread_mutex_unlock(&(table->meal_check));
			break ;
		}
		usleep(100);
	}
}

void	death_checker(t_table *table)
{
	int	i;

	while (!(table->all_ate))
	{
		look_for_death(table);
		pthread_mutex_lock(&(table->meal_check));
		if (table->smbd_has_died)
		{
			pthread_mutex_unlock(&(table->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(table->meal_check));
		i = 0;
		pthread_mutex_lock(&(table->meal_check));
		while (i < table->nb_philo
			&& table->philoso[i].how_many_times_eat >= table->nb_must_eat)
			i++;
		pthread_mutex_unlock(&(table->meal_check));
		if (i == table->nb_philo)
			table->all_ate = 1;
	}
}

void	*moni_philo(void *void_table)
{
	t_table	*table;

	table = (t_table *)void_table;
	while (1)
	{
		death_checker(table);
		usleep(100);
	}
	return (NULL);
}
