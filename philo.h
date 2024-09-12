/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:46:37 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/12 17:48:36 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h> 
#include <pthread.h>


typedef struct		s_philo
{
	int 	id;
	int		time_has_eat;
	int		left_fork;
	int		right_fork;
	int 	time_of_last_meal;
	pthread_t		thread_id;			
}					t_philo;



typedef struct		s_monitoring
{
	int 	nb_philo;
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	int		nb_of_time_eating;
	int 	smbd_has_died;
	int 	all_ate;
	
}					t_data;

#endif