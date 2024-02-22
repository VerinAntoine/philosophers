/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:58:11 by averin            #+#    #+#             */
/*   Updated: 2024/02/22 14:50:09 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_starving(t_philo *philo, t_param param)
{
	return (get_miliseconds() - philo->status.action_time > param.time_to_die);
}

static void	set_status(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->status.mutex);
	philo->status.value = action;
	philo->status.action_time = get_miliseconds();
	pthread_mutex_unlock(&philo->status.mutex);
}

int	get_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->status.mutex);
	status = philo->status.value;
	pthread_mutex_unlock(&philo->status.mutex);
	return (status);
}

static void	do_die(t_philo *philo)
{
	print_status(philo, "has died");
	set_status(philo, DEAD);
}

static void	do_sleep(t_philo *philo, t_param param)
{
	print_status(philo, "is sleeping");
	set_status(philo, SLEEP);
	usleep(param.time_to_sleep * 1000);
}

static int	do_eat(t_philo *philo, t_param param)
{
	print_status(philo, "is thinking");
	set_status(philo, THINK);
	// if (philo->number % 2)
	// {
		while (get_var(philo->left_fork) != 0)
		{
			if (is_starving(philo, param))
				return (do_die(philo), 1);
			usleep(1 * 1000);
		}
		set_var(philo->left_fork, philo->number);
		print_status(philo, "has taken left fork");
		while (get_var(philo->right_fork) != 0)
		{
			if (is_starving(philo, param))
				return (do_die(philo), 1);
			usleep(1 * 1000);
		}
		set_var(philo->right_fork, philo->number);
		print_status(philo, "has taken right fork");
	// }
	// else
	// {
	// 	while (get_var(philo->right_fork) != 0)
	// 		;
	// 	set_var(philo->right_fork, philo->number);
	// 	print_status(philo, "has taken right fork");
	// 	while (get_var(philo->left_fork) != 0)
	// 		;
	// 	set_var(philo->left_fork, philo->number);
	// 	print_status(philo, "has taken left fork");
	// }
	print_status(philo, "is eating");
	set_status(philo, EAT);
	usleep(param.time_to_eat * 1000);
	set_var(philo->left_fork, 0);
	set_var(philo->right_fork, 0);
	return (0);
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
		// if (philo->number % 2)
		// {
			do_eat(philo, philo->data->param);
			if (get_status(philo) == DEAD
				|| get_var(&philo->data->state) != RUNNING)
				return (print_status(philo, "has starved"), NULL);
			do_sleep(philo, philo->data->param);
			if (get_status(philo) == DEAD
				|| get_var(&philo->data->state) != RUNNING)
				return (print_status(philo, "has starved"), NULL);
		// }
		// else
		// {
		// 	do_sleep(philo, philo->data->param);
		// 	do_eat(philo, philo->data->param);
		// }
	}
	// print_status(philo, "has finished");
	set_status(philo, FINISHED);
	return (0);
}
