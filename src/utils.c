/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:16:50 by agtshiba          #+#    #+#             */
/*   Updated: 2024/10/03 18:17:46 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	init_starttime(void)
{
	struct timeval	tv;
	long long		start_time;

	start_time = 0;
	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (start_time);
}

long long	gettimestamp(t_table *table)
{
	struct timeval	tv;
	long long		start_time;
	long long		current_time;

	start_time = table->start_time;
	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	//return (current_time);
	return (current_time - start_time);
}

void	print_time(const char *message)
{
	time_t		raw_time;
	struct tm	*time_info;
	char		buffer[80];

	time(&raw_time);
	time_info = localtime(&raw_time);
	strftime(buffer, sizeof(buffer), "%H:%M:%S - %d/%m/%Y", time_info);
	printf("%s: %s\n", message, buffer);
}

void	smart_sleep(long long time, t_table *table)
{
	long long	i;

	i = gettimestamp(table);
	while (!(table->smbd_has_died))
	{
		if ((gettimestamp(table) - i) >= time)
			break ;
		usleep(50);
	}
}

void	action_print(t_table *table, int i, char *string)
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	pthread_mutex_lock(&(table->writing));
	if (!(table->smbd_has_died))
	{
		printf("%lli", current_time);
		printf(" philo %d ", i);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(table->writing));
	return ;
}
