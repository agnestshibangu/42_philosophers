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
		philo_sleep(table);
		philo_think(table, philo);
		i++;
		if (table->number_of_times_each_philosopher_must_eat > 0 && 
			i >= table->number_of_times_each_philosopher_must_eat)
			break;
	}
}

// void 	action_print(t_table *table, int i, char *string)
// {
// 	pthread_mutex_lock(&(table->writing));
// 	if (!(table->smbd_has_died))
// 	{
// 		printf("%lli", gettimestamp(table) - table->start_time);
// 		printf("philo %d", i);
// 		printf("%s\n", string);
// 	}
// 	pthread_mutex_unlock(&(table->writing));
// 	return;
// }


void action_print(t_table *table, int i, char *string) {
    pthread_mutex_lock(&(table->writing));
    
    if (!(table->smbd_has_died)) {
        long long elapsed_time = gettimestamp(table) - table->start_time;

        // Convert elapsed time to hours, minutes, and seconds
        long hours = elapsed_time / 3600000; // Assuming elapsed time is in milliseconds
        long minutes = (elapsed_time % 3600000) / 60000;
        long seconds = (elapsed_time % 60000) / 1000;

        // Print the formatted time
        printf("[%02ld:%02ld:%02ld] ", hours, minutes, seconds);
        printf("philo %d: %s\n", i, string);
    }

    pthread_mutex_unlock(&(table->writing));
    return;
}

void 	*philo_eat(t_table *table, t_philo *philo)
{	
	if (philo->id % 2 == 0)
	{
		// FOURCHETTE DE DROITE
		pthread_mutex_lock(&(table->forks[philo->right_fork_id]));
		action_print(table, philo->id, " has taken a fork");

		// pthread_mutex_lock(&(table->writing));
		// printf("philo number %d a la fourchette DROITE n %d\n", philo->id, philo->right_fork_id);
		// pthread_mutex_unlock(&(table->writing));

		// FOURCHETTE DE GAUCHE
		pthread_mutex_lock(&(table->forks[philo->left_fork_id]));
		pthread_mutex_lock(&(table->writing));
		printf("philo number %d a la fourchette GAUCHE n %d\n", philo->id, philo->left_fork_id);
		printf("philo number %d is eating\n", philo->id);
		pthread_mutex_unlock(&(table->writing));
		pthread_mutex_unlock(&(table->forks[philo->right_fork_id]));
		pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));

		
		pthread_mutex_lock(&(table->meal_check));
		philo->time_of_last_meal = gettimestamp(table);
		pthread_mutex_unlock(&(table->meal_check));
		smart_sleep(table->time_to_eat, table);

		pthread_mutex_lock(&(table->meal_check));
		philo->how_many_times_eat += 1;
		pthread_mutex_unlock(&(table->meal_check));

		pthread_mutex_lock(&(table->writing));
		pthread_mutex_lock(&(table->meal_check));
		printf("philo number %d last time of eating %lld \n", philo->id, philo->time_of_last_meal);
		pthread_mutex_unlock(&(table->meal_check));

		printf("philo number %d has eat %d times \n", philo->id, philo->how_many_times_eat);
		pthread_mutex_unlock(&(table->writing));

	}
	else if (philo->id == table->nb_philo - 1 || philo->id % 2 != 0)
	{
		// FOURCHETTE DE GAUCHE
		pthread_mutex_lock(&(table->forks[philo->left_fork_id]));
		pthread_mutex_lock(&(table->writing));
		printf("philo number %d a la fourchette GAUCHE n %d\n", philo->id, philo->left_fork_id);
		pthread_mutex_unlock(&(table->writing));

		// FOURCHETTE DE DROITE
		pthread_mutex_lock(&(table->forks[philo->right_fork_id]));
		pthread_mutex_lock(&(table->writing));
		printf("philo number %d a la fourchette DROITE n %d\n", philo->id, philo->right_fork_id);
		printf("philo number %d is eating\n", philo->id);
		pthread_mutex_unlock(&(table->writing));
		pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));
		pthread_mutex_unlock(&(table->forks[philo->right_fork_id]));
		
		pthread_mutex_lock(&(table->meal_check));
		philo->time_of_last_meal = gettimestamp(table);
		pthread_mutex_unlock(&(table->meal_check));
		smart_sleep(table->time_to_eat, table);

		pthread_mutex_lock(&(table->meal_check));
		philo->how_many_times_eat += 1;
		pthread_mutex_unlock(&(table->meal_check));

		pthread_mutex_lock(&(table->writing));
		pthread_mutex_lock(&(table->meal_check));
		printf("philo number %d last time of eating %lld \n", philo->id, philo->time_of_last_meal);
		pthread_mutex_unlock(&(table->meal_check));

		printf("philo number %d has eat %d times\n", philo->id, philo->how_many_times_eat);
		pthread_mutex_unlock(&(table->writing));
	}
	return (NULL);
}


void		philo_sleep(t_table *table)
{
	smart_sleep(table->time_to_sleep, table);
}


void		philo_think(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&(table->writing));
	printf("philo number %d is thinking 🧘\n\n", philo->id);
	pthread_mutex_unlock(&(table->writing));
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
		pthread_mutex_lock(&(table->meal_check)); // Lock to protect access to time_of_last_meal
		printf("Philosopher %d: Last Meal TIME: %lld\n\n",
			table->philosophers[i].id, table->philosophers[i].time_of_last_meal);
		pthread_mutex_unlock(&(table->meal_check)); // Unlock after accessing time_of_last_meal
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

			// Debugging print to check the values
			// pthread_mutex_lock(&(table->writing));
			// printf("Philosopher %d: Current Time: %lld, Last Meal Time: %lld, Time Since Last Meal: %lld, Time to Die: %d\n",
			//        table->philosophers[i].id, current_time, table->philosophers[i].time_of_last_meal, time_since_last_meal, table->time_to_die);
			// pthread_mutex_unlock(&(table->writing));

			if (time_since_last_meal > table->time_to_die)
			{
				pthread_mutex_lock(&(table->writing));
				printf("philo number %d has died 💀\n", table->philosophers[i].id);
				//pthread_mutex_unlock(&(table->meal_check));
				pthread_mutex_unlock(&(table->writing));
				
				pthread_mutex_lock(&(table->meal_check));
				table->smbd_has_died = 1;
				pthread_mutex_unlock(&(table->meal_check));
				break;
			}
			// pthread_mutex_unlock(&(table->meal_check));
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
	// death_checker(table);
	//print_last_meal_times(table);
	// on join tout les threads
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
