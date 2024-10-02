#include "../philo.h"

void 	*p_thread(void *void_args)
{

	t_table 	*table;
	t_thread_args	*args;
	t_philo 	*philo;

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
	while (1)
	{	
		if (table->smbd_has_died)
			break;
		philo_eat(table, philo);
		philo_sleep(table, philo);
		action_print(table, philo->id, " is thinking");
		i++;
		if (table->number_of_times_each_philosopher_must_eat > 0 && 
			i >= table->number_of_times_each_philosopher_must_eat)
			break;
	}
}

void 	*philo_eat(t_table *table, t_philo *philo)
{	
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(table->forks[philo->right_fork_id]));
		action_print(table, philo->id, " has taken a fork");
		pthread_mutex_lock(&(table->forks[philo->left_fork_id]));
		action_print(table, philo->id, " has taken a fork");
		action_print(table, philo->id, " is eating");
		pthread_mutex_unlock(&(table->forks[philo->right_fork_id]));
		pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));
		pthread_mutex_lock(&(table->meal_check));
		philo->time_of_last_meal = gettimestamp(table);
		philo->how_many_times_eat += 1;
		pthread_mutex_unlock(&(table->meal_check));
		smart_sleep(table->time_to_eat, table);
	}
	else if (philo->id == table->nb_philo - 1 || philo->id % 2 != 0)
	{
		pthread_mutex_lock(&(table->forks[philo->left_fork_id]));
		action_print(table, philo->id, " has taken a fork");
		pthread_mutex_lock(&(table->forks[philo->right_fork_id]));
		action_print(table, philo->id, " has taken a fork");
		action_print(table, philo->id, " is eating");
		pthread_mutex_unlock(&(table->forks[philo->right_fork_id]));
		pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));
		pthread_mutex_lock(&(table->meal_check));
		philo->time_of_last_meal = gettimestamp(table);
		philo->how_many_times_eat += 1;
		pthread_mutex_unlock(&(table->meal_check));
		smart_sleep(table->time_to_eat, table);
	}
	return (NULL);
}

void		philo_sleep(t_table *table, t_philo *philo)
{
	action_print(table, philo->id, " is sleeping");
	smart_sleep(table->time_to_sleep, table);
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

void	print_last_meal_times(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&(table->writing));
		pthread_mutex_lock(&(table->meal_check));
		printf("Philosopher %d: Last Meal TIME: %lld\n\n",
			table->philosophers[i].id, table->philosophers[i].time_of_last_meal);
		pthread_mutex_unlock(&(table->meal_check));
		pthread_mutex_unlock(&(table->writing));
		i++;
	}
}

void	death_checker(t_table *table)
{
	int i;

	while (!(table->all_ate))
	{
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
		{
			table->all_ate = 1;
			pthread_mutex_lock(&(table->writing));
			printf("EVERYBODY ATEEEEEEE !!!!!!\n");
			pthread_mutex_unlock(&(table->writing));
		}
	}
}

void *monitor_philosophers(void *void_table) {
    t_table *table = (t_table *)void_table;
    while (1) {
		death_checker(table);
        usleep(100);
    }
    return NULL;
}

int 	init_all_philosophers(t_table *table)
{
	int i;
	char *tab;
    t_thread_args *thread_args;

	i = 0;
	tab = "threadid";

	if (table->nb_philo == 1)
	{
		action_print(table, table->philosophers[i].id, " has taken a fork");
		action_print(table, table->philosophers[i].id, " is dead 💀 \n");
		return 0;
	}

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
	pthread_t monitor_thread;
    if (pthread_create(&monitor_thread, NULL, monitor_philosophers, (void *)table)) {
        return (1);
    }
	for (i = 0; i < table->nb_philo; i++) {
        pthread_join(table->philosophers[i].thread_id, NULL);
    }
    printf("threads terminated\n");
    return (0);
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
