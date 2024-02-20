/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:57:39 by averin            #+#    #+#             */
/*   Updated: 2024/02/18 21:26:00 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define EMEM 1
# define EGEN 2

# define ERROR_USAGE "Usage: %s number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef struct s_var
{
	pthread_mutex_t	mutex;
	int				content;
}	t_var;

typedef t_var t_fork;

typedef struct s_status
{
	enum	e_action
	{
		TRY_EAT = 1,
		EAT,
		THINK,
		SLEEP,
	}				value;
	pthread_mutex_t	mutex;
	long			action_time;
}	t_status;

enum	e_state
{
	WAITING = 1,
	RUNNING,
	STOPED
};

typedef struct s_param
{
	int	philo_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_number;
}	t_param;

typedef struct s_data
{
	pthread_mutex_t	write;
	t_var			state;
	t_param			param;
}	t_data;

typedef struct s_philo
{
	int			number;
	pthread_t	thread;
	t_status	status;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_data		*data;
}	t_philo;

long	get_miliseconds(void);

int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

int		parse_params(char **argv, t_param *params);
void	print_params(t_param param);

void	*philo_routine(void *ptr);

void	init_var(t_var *var, int val);
void	set_var(t_var *var, int val);
int		get_var(t_var *var);

#endif
