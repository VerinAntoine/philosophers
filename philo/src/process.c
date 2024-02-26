/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:58:11 by averin            #+#    #+#             */
/*   Updated: 2024/02/26 11:11:39 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	do_die(t_philo *philo)
{
	print_status(philo, "died");
	set_var(&philo->data->state, STOPED);
}

static void	do_sleep(t_philo *philo, t_param param)
{
	if (param.time_to_sleep > param.time_to_die + param.time_to_eat)
	{
		usleep((param.time_to_die - param.time_to_eat) * 1000);
		do_die(philo);
		return ;
	}
	print_status(philo, "is sleeping");
	set_var(&philo->status, SLEEP);
	usleep(param.time_to_sleep * 1000);
}

static int	take_forks(t_philo *philo, t_param param)
{
	while (get_var(philo->left_fork) != 0)
	{
		if (get_var(&philo->data->state) != RUNNING)
			return (1);
		if (is_starving(philo, param))
			return (do_die(philo), 1);
		usleep(1 * 1000);
	}
	set_var(philo->left_fork, philo->number);
	print_status(philo, "has taken a fork");
	while (get_var(philo->right_fork) != 0)
	{
		if (get_var(&philo->data->state) != RUNNING)
			return (1);
		if (is_starving(philo, param))
			return (do_die(philo), 1);
		usleep(1 * 1000);
	}
	set_var(philo->right_fork, philo->number);
	print_status(philo, "has taken a fork");
	return (0);
}

static int	do_eat(t_philo *philo, t_param param)
{
	print_status(philo, "is thinking");
	set_var(&philo->status, THINK);
	if (take_forks(philo, param))
		return (1);
	print_status(philo, "is eating");
	set_var(&philo->status, EAT);
	incr_var(&philo->eat_count);
	philo->last_eat = get_miliseconds();
	usleep(param.time_to_eat * 1000);
	set_var(philo->left_fork, 0);
	set_var(philo->right_fork, 0);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (get_var(&philo->data->state) == WAITING)
		usleep(1 * 1000);
	philo->last_eat = get_miliseconds();
	if (philo->number % 2)
		usleep(philo->data->param.time_to_eat * 1000);
	while (get_var(&philo->data->state) == RUNNING)
	{
		do_eat(philo, philo->data->param);
		if (get_var(&philo->data->state) != RUNNING
			|| get_var(&philo->status) == DEAD)
			return (0);
		do_sleep(philo, philo->data->param);
	}
	return (0);
}
