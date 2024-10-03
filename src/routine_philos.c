/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:08:43 by agtshiba          #+#    #+#             */
/*   Updated: 2024/10/03 11:49:06 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void 	*p_thread(void *void_args)
{
	t_table 	*table;
	t_thread_args	*args;
	t_philo		*philo;

	args = (t_thread_args *)void_args;
	table = args->table;
	philo = args->philo;
	philosopher_routine(table, philo);
	free(args);
	return (NULL);
}

void 	philosopher_routine(t_table *table, t_philo *philo)
{
	int i;
	
	i = 0;
	if (table->nb_philo == 1)
	{
		action_print(table, table->philosophers[i].id, " has taken a fork");
		action_print(table, table->philosophers[i].id, " is dead 💀 \n");
		return ;
	}
	while (1)
	{	
		if (table->smbd_has_died)
			break;
		philo_eat(table, philo);
		action_print(table, philo->id, " is sleeping");
		smart_sleep(table->time_to_sleep, table);
		action_print(table, philo->id, " is thinking");
		i++;
		if (table->number_of_times_each_philosopher_must_eat > 0 && 
			i >= table->number_of_times_each_philosopher_must_eat)
			break;
	}
}

void *philo_eat_even(t_table *table, t_philo *philo)
{
    pthread_mutex_lock(&(table->forks[philo->right_fork_id]));
    action_print(table, philo->id, " has taken a fork");
    pthread_mutex_lock(&(table->forks[philo->left_fork_id]));
    action_print(table, philo->id, " has taken a fork");
    action_print(table, philo->id, " is eating");
    pthread_mutex_lock(&(table->meal_check));
    philo->time_of_last_meal = gettimestamp(table);
    philo->how_many_times_eat += 1;
    pthread_mutex_unlock(&(table->meal_check));
    smart_sleep(table->time_to_eat, table);
    pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));
    pthread_mutex_unlock(&(table->forks[philo->right_fork_id]));
    return (NULL);
}

void *philo_eat_odd(t_table *table, t_philo *philo)
{
    pthread_mutex_lock(&(table->forks[philo->left_fork_id]));
    action_print(table, philo->id, " has taken a fork");
    pthread_mutex_lock(&(table->forks[philo->right_fork_id]));
    action_print(table, philo->id, " has taken a fork");
    action_print(table, philo->id, " is eating");
    pthread_mutex_lock(&(table->meal_check));
    philo->time_of_last_meal = gettimestamp(table);
    philo->how_many_times_eat += 1;
    pthread_mutex_unlock(&(table->meal_check));
    smart_sleep(table->time_to_eat, table);
    pthread_mutex_unlock(&(table->forks[philo->right_fork_id]));
    pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));
    return (NULL);
}

void *philo_eat(t_table *table, t_philo *philo){
    if (philo->id % 2 == 0) {
        return philo_eat_even(table, philo);
    } else {
        return philo_eat_odd(table, philo);
    }
}

/// Debugg

// void	death_checker(t_table *table)
// {
// 	int i;

// 	while (!(table->all_ate))
// 	{
// 		i = -1;
// 		while (++i < table->nb_philo)
// 		{
// 			long long current_time = gettimestamp(table);
			
// 			pthread_mutex_lock(&(table->meal_check));
// 			long long time_since_last_meal = current_time - table->philosophers[i].time_of_last_meal;
// 			pthread_mutex_unlock(&(table->meal_check));

// 			if (time_since_last_meal > table->time_to_die)
// 			{
// 				action_print(table, table->philosophers[i].id, " is dead 💀 \n");
// 				pthread_mutex_lock(&(table->meal_check));
// 				table->smbd_has_died = 1;
// 				pthread_mutex_unlock(&(table->meal_check));
// 				break;
// 			}
// 			usleep(100);
// 		}
// 		pthread_mutex_lock(&(table->meal_check));
// 		if (table->smbd_has_died)
// 		{
// 			pthread_mutex_unlock(&(table->meal_check));
// 			break;
// 		}
// 		pthread_mutex_unlock(&(table->meal_check));
// 		i = 0;
// 		pthread_mutex_lock(&(table->meal_check));
// 		while (i < table->nb_philo && table->philosophers[i].how_many_times_eat >= table->number_of_times_each_philosopher_must_eat)
// 			i++;
// 		pthread_mutex_unlock(&(table->meal_check));
		
// 		if (i == table->nb_philo)
// 		{
// 			table->all_ate = 1;
// 			pthread_mutex_lock(&(table->writing));
// 			printf("EVERYBODY ATEEEEEEE !!!!!!\n");
// 			pthread_mutex_unlock(&(table->writing));
// 		}
// 	}
// }