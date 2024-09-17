#include "../philo.h"

pthread_mutex_t 	print_mutex;

void *routine_philo(void *data)
{
	int nb;
	nb = *(int *)data;

	pthread_mutex_lock(&print_mutex);
	printf("philo number %d is starting to think\n", nb);
	printf("\n");
	usleep(1000 * 2000);
	printf("philo number %d is taking the left fork\n", nb);
	printf("philo number %d is taking the right fork\n", nb);
	printf("philo number %d is starting to eat\n", nb);
	printf("\n");
	usleep(1000 * 2000);
	printf("philo number %d is putting down his forks\n", nb);
	printf("philo number %d is starting to sleep\n", nb);
	printf("\n");
	usleep(1000 * 2000);
	printf("\n");
	
	pthread_mutex_unlock(&print_mutex);

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

int 	init_all_philosophers(t_table *table, int nb_philos)
{
	int i;
	char *tab;

	i = 0;
	tab = "threadid";

	while (i < table->nb_philos)
	{
		table->philosophers[i].id = i;
		table->philosophers[i].how_many_times_eat = 0;
		table->philosophers[i].right_fork_id = i;
		table->philosophers[i].left_fork_id = i + 1;
		if (i == nb_philos)
			table->philosophers[i].left_fork_id = 0;
		table->philosophers[i].time_of_last_meal = 0;
		table->philosophers[i].thread_id_name = ft_strjoin(tab, ft_itoa(i));
		// printf("one philo has been created ! \n");
		i++;
	}
	while (++i <= table->nb_philos)
		if (pthread_create(&(philosophers[i].thread_id_name), NUULL, ))
	return (0);
}

int 	init_table(t_table *table, char **av)
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
// PARAMS
/// 1 number_of_philosophers
/// 2 time_to_die
/// 3 time_to_eat
/// 4 time_to_sleep
/// 5 [number_of_times_each_philosopher_must_eat]

int main(int ac, char **av)
{
	t_table table;

	init_table(&table, av);
	init_philosophers(&table);

	// mutex
	// pthread_mutex_init(&print_mutex, NULL);
	// thread
	// while ()
	// {
	// 	pthread_create(&threadid1, NULL, routine_philo, nb1);
	// 	pthread_join(threadid1, NULL);
	// }
	
	// mutex
	// pthread_mutex_destroy(&print_mutex);

	// // one thread
	// 	// mutex
	// pthread_mutex_init(&print_mutex, NULL);
	// // thread
	// pthread_create(&threadid1, NULL, routine_philo, nb1);
	// pthread_join(threadid1, NULL);
	// // mutex
	// pthread_mutex_destroy(&print_mutex);
	
	return (0);
}




// int main(void)
// {
// 	pthread_t threadid1;
// 	pthread_t threadid2;

// 	pthread_mutex_init(&print_mutex, NULL);

// 	int *nb1 = malloc(sizeof(int));
// 	int	*nb2 = malloc(sizeof(int));

// 	*nb1 = 1;
// 	*nb2 = 2;


// 	pthread_create(&threadid1, NULL, routine_philo, nb1);
// 	pthread_create(&threadid2, NULL, routine_philo, nb2);

// 	pthread_join(threadid1, NULL);
// 	pthread_join(threadid2, NULL);
	
// 	pthread_mutex_destroy(&print_mutex);
	
// 	return (0);
// }