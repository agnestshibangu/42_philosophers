#include "../philo.h"

int main(int ac, char **av)
{
	(void)ac;
	t_table table;

	int i;

	i = 0;
	print_time("Le programme a commence a : ");
	init_table(&table, av);
	init_mutex(&table);
	c_d_philo_threads(&table);
	print_time("Le programme a termine a : ");

	while (table.philosophers[i].thread_id_name)
	{
		free(table.philosophers[i].thread_id_name);
		i++;
	} 

	return (0);
}