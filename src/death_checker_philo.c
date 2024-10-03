/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:23:55 by agtshiba          #+#    #+#             */
/*   Updated: 2024/10/03 11:39:13 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void 	look_for_death(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->nb_philo)
	{
		long long current_time = gettimestamp(table);
		
		pthread_mutex_lock(&(table->meal_check));
		long long time_since_last_meal = current_time - table->philosophers[i].time_of_last_meal;
		pthread_mutex_unlock(&(table->meal_check));

		if (time_since_last_meal > table->time_to_die)
		{
			action_print(table, table->philosophers[i].id, " is dead 💀 \n");
			pthread_mutex_lock(&(table->meal_check));
			table->smbd_has_died = 1;
			pthread_mutex_unlock(&(table->meal_check));
			break;
		}
		usleep(100);
	}	
}

void	death_checker(t_table *table)
{
	int i;

	while (!(table->all_ate))
	{
		look_for_death(table);
		pthread_mutex_lock(&(table->meal_check));
		if (table->smbd_has_died)
		{
			pthread_mutex_unlock(&(table->meal_check));
			break;
		}
		pthread_mutex_unlock(&(table->meal_check));
		i = 0;
		pthread_mutex_lock(&(table->meal_check));
		while (i < table->nb_philo && table->philosophers[i].how_many_times_eat >= table->number_of_times_each_philosopher_must_eat)
			i++;
		pthread_mutex_unlock(&(table->meal_check));
		if (i == table->nb_philo)
			table->all_ate = 1;
	}
}

void *monitor_philosophers(void *void_table) 
{
    t_table *table = (t_table *)void_table;
    while (1) {
		death_checker(table);
        usleep(100);
    }
    return NULL;
}
