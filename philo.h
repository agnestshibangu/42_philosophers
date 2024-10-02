/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:46:37 by agtshiba          #+#    #+#             */
/*   Updated: 2024/10/02 18:18:50 by agtshiba         ###   ########.fr       */
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
	long long 	time_of_last_meal;
	char 	*thread_id_name;
	pthread_t		thread_id;			
}					t_philo;

typedef struct		s_table
{
	long long start_time;
	int 	nb_philo;
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
	int 	smbd_has_died;
	int 	all_ate;
	t_philo		philosophers[250];
	pthread_mutex_t		meal_check;
	pthread_mutex_t 	writing;
	pthread_mutex_t		forks[250];
	pthread_t	monitoring;
	
}					t_table;

typedef struct s_thread_args
{
	t_philo	*philo;
	t_table	*table;
}	t_thread_args;


int	ft_atoi(char *str);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

void 	philosopher_routine(t_table *table, t_philo *philo);
void 	action_print(t_table *table, int i, char *string);

int 	init_mutex(t_table *table);
int 	init_all_philosophers(t_table *table);
void 	*philo_eat(t_table *table, t_philo *philo);
// void	philo_sleep(t_table *table, t_philo *philo);
void		philo_sleep(t_table *table, t_philo *philo);
// void		philo_sleep(t_table *table);
void	philo_think(t_table *table, t_philo *philo);
void 	init_table(t_table *table, char **av);


long long init_starttime();

long long gettimestamp(t_table *table);
void *monitor_philosophers(void *void_table);


// void	death_checker(t_table *table);
// long long 	time_diff(long long past, long long present);
// void print_starting_time(void);
// void print_finishing_time(void);
void print_time(const char *message);
// void join_and_terminate(t_table *table);

void 	smart_sleep(long long time, t_table *table);


void	print_last_meal_times(t_table *table);
// static size_t	calculate_size(long number);


#endif