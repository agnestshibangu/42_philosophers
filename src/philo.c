#include "../philo.h"

int main(int ac, char **av)
{
	(void)ac;
	t_table table;

	print_time("Le programme a commence a : ");
	init_table(&table, av);
	init_all_philosophers(&table);
	init_mutex(&table);
	print_time("Le programme a termine a : ");

	return (0);
}