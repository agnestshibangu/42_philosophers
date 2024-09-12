#include "../philo.h"

pthread_mutex_t 	print_mutex;

void *routine_philo(void *data)
{
	// eat sleep think

	int nb;
	nb = *(int *)data;

	pthread_mutex_lock(&print_mutex);
	printf("philo number %d is taking the left fork\n", nb);
	printf("philo number %d is taking the right fork\n", nb);
	printf("philo number %d is starting to eat\n", nb);
	pthread_mutex_unlock(&print_mutex);

	sleep(1);

	pthread_mutex_lock(&print_mutex);
	printf("philo number %d is starting to sleep\n", nb);
	printf("philo number %d is starting to think\n", nb);
	pthread_mutex_unlock(&print_mutex);

	return (NULL);
}


int main(void)
{
	pthread_t threadid1;
	pthread_t threadid2;

	int nb = 1;	

	pthread_mutex_init(&print_mutex, NULL);

	pthread_create(&threadid1, NULL, routine_philo, &nb);
	
	pthread_create(&threadid2, NULL, routine_philo, &nb);

	pthread_join(threadid1, NULL);
	pthread_join(threadid2, NULL);

	pthread_mutex_destroy(&print_mutex);

	return (0);
}