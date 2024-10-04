/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:49:45 by agtshiba          #+#    #+#             */
/*   Updated: 2024/10/04 11:58:27 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i <= table->nb_philo)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(table->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(table->meal_check), NULL))
		return (1);
	return (0);
}

int	init_philos(t_table *table)
{
	char	*tab;
	int		i;

	i = 0;
	tab = "threadid";
	if (!table)
		return (1);
	while (i < table->nb_philo)
	{
		table->philoso[i].id = i + 1;
		table->philoso[i].how_many_times_eat = 0;
		table->philoso[i].right_fork_id = i;
		table->philoso[i].left_fork_id = (i + 1) % table->nb_philo;
		table->philoso[i].time_of_last_meal = 0;
		table->philoso[i].thread_id_name = ft_strjoin(tab, ft_itoa(i));
		i++;
	}
	return (0);
}

int	c_d_philo_threads(t_table *table)
{
	t_thread_args	*thread_args;
	pthread_t		monitor_thread;
	pthread_t		*thread_id;
	int				i;

	init_philos(table);
	i = 0;
	while (i < table->nb_philo)
	{
		thread_id = &(table->philoso[i].thread_id);
		thread_args = malloc(sizeof(t_thread_args));
		if (!thread_args)
			return (1);
		thread_args->philo = &(table->philoso[i]);
		thread_args->table = table;
		if (pthread_create(thread_id, NULL, p_thread, (void *)thread_args))
			return (free(thread_args), 1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, moni_philo, (void *)table))
		return (1);
	join_philosopher_threads(table);
	return (0);
}

void	join_philosopher_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philoso[i].thread_id, NULL);
		i++;
	}
	printf("threads terminated\n");
}

int	init_table(t_table *table, char **av)
{
	if (!table)
		return (1);
	table->start_time = init_starttime();
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->nb_must_eat = ft_atoi(av[5]);
	else
		table->nb_must_eat = 0;
	table->all_ate = 0;
	table->smbd_has_died = 0;
	return (0);
}
