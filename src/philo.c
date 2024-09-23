#include "../philo.h"

int main(int ac, char **av)
{
	(void)ac;
	t_table table;

	print_starting_time();
	init_table(&table, av);
	init_all_philosophers(&table);
	init_mutex(&table);
	print_finishing_time();

	return (0);
}