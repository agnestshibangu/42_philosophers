/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:08:43 by agtshiba          #+#    #+#             */
/*   Updated: 2024/10/03 17:24:51 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*p_thread(void *void_args)
{
	t_table			*table;
	t_philo			*philo;
	t_thread_args	*args;

	args = (t_thread_args *)void_args;
	table = args->table;
	philo = args->philo;
	philosopher_routine(table, philo);
	free(args);
	return (NULL);
}

void	philosopher_routine(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	if (table->nb_philo == 1)
	{
		action_print(table, table->philoso[i].id, " has taken a fork");
		action_print(table, table->philoso[i].id, " is dead 💀 \n");
		return ;
	}
	while (1)
	{
		if (table->smbd_has_died)
			break ;
		philo_eat(table, philo);
		action_print(table, philo->id, " is sleeping");
		smart_sleep(table->time_to_sleep, table);
		action_print(table, philo->id, " is thinking");
		i++;
		if (table->nb_must_eat > 0
			&& i >= table->nb_must_eat)
			break ;
	}
}

void	*philo_eat_even(t_table *table, t_philo *philo)
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

void	*philo_eat_odd(t_table *table, t_philo *philo)
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

void	*philo_eat(t_table *table, t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo_eat_even(table, philo));
	else
		return (philo_eat_odd(table, philo));
}
