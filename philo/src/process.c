/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:58:11 by averin            #+#    #+#             */
/*   Updated: 2024/02/20 13:47:25 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_status(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->status.mutex);
	philo->status.value = action;
	philo->status.action_time = get_miliseconds();
	pthread_mutex_unlock(&philo->status.mutex);
}

static void	do_sleep(t_philo *philo, t_param param)
{
	printf("[%ld] %d is sleeping\n", get_miliseconds(), philo->number);
	set_status(philo, SLEEP);
	usleep(param.time_to_sleep);
}

static void	do_eat(t_philo *philo, t_param param)
{
	printf("[%ld] %d is thinking\n", get_miliseconds(), philo->number);
	set_status(philo, THINK);
	if (philo->number % 2)
	{
		while (get_var(philo->left_fork) != 0)
			;
		set_var(philo->left_fork, 1);
		printf("[%ld] %d has taken left fork\n", get_miliseconds(), philo->number);
		while (get_var(philo->right_fork) != 0)
			;
		set_var(philo->right_fork, 1);
		printf("[%ld] %d has taken right fork\n", get_miliseconds(), philo->number);
	}
	else
	{
		while (get_var(philo->right_fork) != 0)
			;
		set_var(philo->right_fork, 1);
		printf("[%ld] %d has taken right fork\n", get_miliseconds(), philo->number);
		while (get_var(philo->left_fork) != 0)
			;
		set_var(philo->left_fork, 1);
		printf("[%ld] %d has taken left fork\n", get_miliseconds(), philo->number);
	}
	
	printf("[%ld] %d is eating\n", get_miliseconds(), philo->number);
	set_status(philo, EAT);
	usleep(param.time_to_eat);
	set_var(philo->left_fork, 0);
	set_var(philo->right_fork, 0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = ptr;
	while (get_var(&philo->data->state) == WAITING)	
		;
	i = -1;
	while (philo->data->param.eat_number == -1
		|| ++i < philo->data->param.eat_number)
	{
		if (philo->number % 2)
		{
			do_eat(philo, philo->data->param);
			do_sleep(philo, philo->data->param);
		}
		else
		{
			do_sleep(philo, philo->data->param);
			do_eat(philo, philo->data->param);
		}
	}
	return (0);
}
