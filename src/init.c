#include "../philo.h"


void 	*p_thread(void *void_args)
{
	int i;
	t_table 	*table;
	t_thread_args	*args;
	t_philo 	*philo;

	i = 0;
	args = (t_thread_args *)void_args;
	table = args->table;
	philo = args->philo;

	philo_eat(*table, *philo);

	free(args);
	return (NULL);
}

void 	*philo_eat(t_table table, t_philo philo)
{	

	if (philo.id % 2 == 0)
	{
		usleep(1000);
		// FOURCHETTE DE DROITE
		pthread_mutex_lock(&(table.forks[philo.right_fork_id]));
		
		pthread_mutex_lock(&(table.writing));
		printf("philo number %d a la fourchette DROITE n %d\n", philo.id, philo.right_fork_id);
		pthread_mutex_unlock(&(table.writing));

		// FOURCHETTE DE GAUCHE
		pthread_mutex_lock(&(table.forks[philo.left_fork_id]));

		pthread_mutex_lock(&(table.writing));
		printf("philo number %d a la fourchette GAUCHE n %d\n", philo.id, philo.left_fork_id);
		printf("philo number %d is eating\n\n", philo.id);
		pthread_mutex_lock(&(table.meal_check));
		philo.time_of_last_meal = timestamp();
		philo.how_many_times_eat += 1;
		pthread_mutex_unlock(&(table.meal_check));
		pthread_mutex_unlock(&(table.writing));

		pthread_mutex_lock(&(table.writing));
		printf("philo number %d has eat %d\n", philo.id, philo.how_many_times_eat);
		pthread_mutex_unlock(&(table.writing));



	}
	else if (philo.id == table.nb_philo - 1 || philo.id % 2 != 0)
	{
		// FOURCHETTE DE GAUCHE
		pthread_mutex_lock(&(table.forks[philo.left_fork_id]));

		pthread_mutex_lock(&(table.writing));
		printf("philo number %d a la fourchette GAUCHE n %d\n", philo.id, philo.left_fork_id);
		pthread_mutex_unlock(&(table.writing));

		// FOURCHETTE DE DROITE
		pthread_mutex_lock(&(table.forks[philo.right_fork_id]));
		
		pthread_mutex_lock(&(table.writing));
		printf("philo number %d a la fourchette DROITE n %d\n", philo.id, philo.right_fork_id);
		printf("philo number %d is eating\n\n", philo.id);
		pthread_mutex_lock(&(table.meal_check));
		philo.how_many_times_eat = timestamp();
		philo.how_many_times_eat += 1;
		pthread_mutex_unlock(&(table.meal_check));
		pthread_mutex_unlock(&(table.writing));

		pthread_mutex_lock(&(table.writing));
		printf("philo number %d has eat %d\n", philo.id, philo.how_many_times_eat);
		pthread_mutex_unlock(&(table.writing));
	}

	// // UNLOCK FOURCHETTE
	// pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));
	// pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));

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
    t_thread_args *thread_args;  // Pointer to dynamically allocate args per thread

	i = 0;
	tab = "threadid";

	// on cree chaque philo a partir de la structure
	while (i < table->nb_philo)
	{
		table->philosophers[i].id = i;
		table->philosophers[i].how_many_times_eat = 0;
		table->philosophers[i].right_fork_id = i;
		table->philosophers[i].left_fork_id = (i + 1) % table->nb_philo;
		table->philosophers[i].time_of_last_meal = 0;
		table->philosophers[i].thread_id_name = ft_strjoin(tab, ft_itoa(i));
		// printf("one philo has been created ! \n");
		i++;
	}

	// pour chaque philo on lance un thread
    i = 0;
	while (i < table->nb_philo)
    {
        thread_args = malloc(sizeof(t_thread_args));  // Allocate new thread_args for each philosopher
        if (!thread_args)
            return (1);  // Handle memory allocation failure

        thread_args->philo = &(table->philosophers[i]);
        thread_args->table = table;

        if (pthread_create(&(table->philosophers[i].thread_id), NULL, p_thread, (void *)thread_args))
        {
            free(thread_args);  // Clean up on failure
            return (1);
        }
        i++;
    }
	// on join tout les threads
	for (i = 0; i < table->nb_philo; i++) {
        pthread_join(table->philosophers[i].thread_id, NULL);
    }
    printf("j ai reussi a lancer tous les threads");
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
