/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:46:37 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/17 17:24:52 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h> 
#include <pthread.h>
#include <stdlib.h>


typedef struct		s_philo
{
	int 	id;
	int		how_many_times_eat;
	int 	left_fork_id;
	int 	right_fork_id;
	int 	time_of_last_meal;
	char 	*thread_id_name;
	pthread_t		thread_id;			
}					t_philo;

typedef struct		s_table
{
	int 	nb_philo;
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	int		nb_of_time_eating;
	int 	smbd_has_died;
	int 	all_ate;
	t_philo		philosophers[250];
	pthread_mutex_t		meal_check;
	pthread_mutex_t 	writing;
	pthread_mutex_t		forks[250];
	pthread_t	monitoring;
	
}					t_table;

int	ft_atoi(char *str);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
// static size_t	calculate_size(long number);


#endif