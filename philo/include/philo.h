/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:57:39 by averin            #+#    #+#             */
/*   Updated: 2024/02/15 10:24:12 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define ERROR_USAGE "Usage: %s number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef pthread_mutex_t t_fork;

typedef struct s_param
{
	int	philo_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_number;
}	t_param;

typedef struct s_philo
{
	enum
	{
		TRY_EAT,
		EAT,
		THINK,
		SLEEP
	}	action;
	pthread_t	thread;
	long		action_time;
}	t_philo;

typedef struct s_data
{
	int		running;
	t_philo	*philos;
	t_fork	*forks;
	t_param	param;
}	t_data;

int		ft_atoi(const char *nptr);

int		parse_params(char **argv, t_param *params);
void	print_params(t_param param);

#endif
