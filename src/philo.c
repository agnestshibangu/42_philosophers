#include "../philo.h"

void 	free_table(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nb_philo)
	{
		free(table->philosophers[i].thread_id_name);
		i++;
	}
}

int main(int ac, char **av)
{
	(void)ac;
	t_table table;

	print_time("Le programme a commence a : ");
	init_table(&table, av);
	init_mutex(&table);
	c_d_philo_threads(&table);
	free_table(&table);
	print_time("Le programme a termine a : ");
	return (0);
}