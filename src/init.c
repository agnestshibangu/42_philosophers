/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:49:45 by agtshiba          #+#    #+#             */
/*   Updated: 2024/10/03 14:20:41 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int 	init_mutex(t_table *table)
{
	int i;

	i = 0;
	while (i <= table->nb_philo)
	{
		if(pthread_mutex_init(&(table->forks[i]), NULL))
			return (1);
		i++;
	}
	if(pthread_mutex_init(&(table->writing), NULL))
		return (1);
	if(pthread_mutex_init(&(table->meal_check), NULL))
		return (1);
	return (0);
}


void	init_philos(t_table *table)
{
	char *tab;
	int i;
	
	i = 0;
	tab = "threadid";
	while (i < table->nb_philo)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].how_many_times_eat = 0;
		table->philosophers[i].right_fork_id = i;
		table->philosophers[i].left_fork_id = (i + 1) % table->nb_philo;
		table->philosophers[i].time_of_last_meal = 0;
		table->philosophers[i].thread_id_name = ft_strjoin(tab, ft_itoa(i));
		i++;
	}
}

int 	c_d_philo_threads(t_table *table)
{
	int i;
	t_thread_args *thread_args;
	pthread_t monitor_thread;

	init_philos(table);
	i = 0;
	while (i < table->nb_philo)
	{
		thread_args = malloc(sizeof(t_thread_args));  
		if (!thread_args)
			return (1);  
		thread_args->philo = &(table->philosophers[i]);
		thread_args->table = table;
		if (pthread_create(&(table->philosophers[i].thread_id), NULL, p_thread, (void *)thread_args))
		{
			free(thread_args);  
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_philosophers, (void *)table)) {
		return (1);
	}
	join_philosopher_threads(table);
	return (0);
}

void join_philosopher_threads(t_table *table)
{
	int i;

	i = 0;
	while(i < table->nb_philo)
	{
		pthread_join(table->philosophers[i].thread_id, NULL);
		i++;
	}
	printf("threads terminated\n");
}

void 	init_table(t_table *table, char **av)
{
	table->start_time = init_starttime();
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		table->number_of_times_each_philosopher_must_eat = 0;
	table->all_ate = 0;
	table->smbd_has_died = 0;
}
