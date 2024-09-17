
#include "../philo.h"

void 	*p_thread(void *void_args)
{	
	int i;
	t_table 	*table;
	t_thread_args	*args;

	i = 0;
	args = (t_thread_args *)void_args;
	
	table = args->table;

    printf("je suis dans le thread");

	while(i < table->nb_philo)
	{
		printf("philo number %d is starting to think\n", table->philosophers[i].id);
		i++;
	}
	return (NULL);
}

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

int 	init_all_philosophers(t_table *table)
{
	int i;
	char *tab;
    t_thread_args thread_args;

	i = 0;
    thread_args.philo = &(table->philosophers[i]);
    thread_args.table = table;

	tab = "threadid";

	while (i < table->nb_philo)
	{
		table->philosophers[i].id = i;
		table->philosophers[i].how_many_times_eat = 0;
		table->philosophers[i].right_fork_id = i;
		table->philosophers[i].left_fork_id = i + 1;
		if (i == table->nb_philo)
			table->philosophers[i].left_fork_id = 0;
		table->philosophers[i].time_of_last_meal = 0;
		table->philosophers[i].thread_id_name = ft_strjoin(tab, ft_itoa(i));
		// printf("one philo has been created ! \n");
		i++;
	}
    i = 0;
	while (++i <= table->nb_philo)
    {
        if (pthread_create(&(table->philosophers[i].thread_id), NULL, p_thread, &thread_args))
            return (1);
    }
    printf("j ai reussi a lancer tout les threads");
    return (0);
}

void 	init_table(t_table *table, char **av)
{
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	table->all_ate = 0;
	table->smbd_has_died = 0;
}
