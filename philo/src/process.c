/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:58:11 by averin            #+#    #+#             */
/*   Updated: 2024/02/23 17:13:41 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_starving(t_philo *philo, t_param param)
{
	// long ms = get_miliseconds();
	// if (ms - philo->last_eat > param.time_to_die)
	// {
	// 	pthread_mutex_lock(&philo->data->write);
	// 	printf(" * %ld - %ld = %ld\n", ms, philo->last_eat, philo->last_eat - ms);
	// 	pthread_mutex_unlock(&philo->data->write);
	// }
	return (get_miliseconds() - philo->last_eat > param.time_to_die);
}

static void	do_die(t_philo *philo)
{
	print_status(philo, "died");
	// set_var(&philo->status, DEAD);
	set_var(&philo->data->state, STOPED);
}

static void	do_sleep(t_philo *philo, t_param param)
{
	if (param.time_to_sleep > param.time_to_die)
	{
		usleep(param.time_to_die * 1000);
		do_die(philo);
		return ;
	}
	print_status(philo, "is sleeping");
	set_var(&philo->status, SLEEP);
	usleep(param.time_to_sleep * 1000);
}

static int	do_eat(t_philo *philo, t_param param)
{
	print_status(philo, "is thinking");
	set_var(&philo->status, THINK);
	while (get_var(philo->left_fork) != 0)
	{
		if (get_var(&philo->data->state) != RUNNING)
			return (0);
		if (is_starving(philo, param))
			return (do_die(philo), 1);
		usleep(1 * 1000);
	}
	set_var(philo->left_fork, philo->number);
	print_status(philo, "has taken a fork");
	while (get_var(philo->right_fork) != 0)
	{
		if (get_var(&philo->data->state) != RUNNING)
			return (0);
		if (is_starving(philo, param))
			return (do_die(philo), 1);
		usleep(1 * 1000);
	}
	set_var(philo->right_fork, philo->number);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	set_var(&philo->status, EAT);
	incr_var(&philo->eat_count);
	usleep(param.time_to_eat * 1000);
	philo->last_eat = get_miliseconds();
	set_var(philo->left_fork, 0);
	set_var(philo->right_fork, 0);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	// int		start;

	philo = ptr;
	while (get_var(&philo->data->state) == WAITING)	
		usleep(1 * 1000);
	philo->last_eat = get_miliseconds();
	// start = philo->number % 2;
	while (get_var(&philo->data->state) == RUNNING)
	{
		// if (!start)
		do_eat(philo, philo->data->param);
		if (get_var(&philo->data->state) != RUNNING
			|| get_var(&philo->status) == DEAD)
			return (0);
		do_sleep(philo, philo->data->param);
		// start = 0;
	}
	return (0);
}
