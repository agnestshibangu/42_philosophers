#include "../philo.h"

// pthread_mutex_t 	print_mutex;

// void *routine_philo(void *data)
// {
// 	int nb;
// 	nb = *(int *)data;

// 	pthread_mutex_lock(&print_mutex);
// 	printf("philo number %d is starting to think\n", nb);
// 	printf("\n");
// 	usleep(1000 * 2000);
// 	printf("philo number %d is taking the left fork\n", nb);
// 	printf("philo number %d is taking the right fork\n", nb);
// 	printf("philo number %d is starting to eat\n", nb);
// 	printf("\n");
// 	usleep(1000 * 2000);
// 	printf("philo number %d is putting down his forks\n", nb);
// 	printf("philo number %d is starting to sleep\n", nb);
// 	printf("\n");
// 	usleep(1000 * 2000);
// 	printf("\n");
	
// 	pthread_mutex_unlock(&print_mutex);

// 	return (NULL);
// }




int main(int ac, char **av)
{
	(void)ac;
	// (void)av;
	t_table table;

	init_table(&table, av);
	init_all_philosophers(&table);
	init_mutex(&table);

	int i = 0;

	while (i < table.nb_philo)
	{
		pthread_join(table.philosophers[i].thread_id, NULL);
	}
	
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