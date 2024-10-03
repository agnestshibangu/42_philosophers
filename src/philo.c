/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:03:44 by agtshiba          #+#    #+#             */
/*   Updated: 2024/10/03 18:02:48 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		free(table->philoso[i].thread_id_name);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (printf("error : too much or too many arguments"), 1);
	print_time("Le programme a commence a : ");
	if (init_table(&table, av) || init_mutex(&table))
		return (printf("error : issue with init"), 1);
	if (c_d_philo_threads(&table))
		return (printf("error : lauching threads"), 1);
	free_table(&table);
	print_time("Le programme a termine a : ");
	return (0);
}
