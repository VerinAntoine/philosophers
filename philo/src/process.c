/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:58:11 by averin            #+#    #+#             */
/*   Updated: 2024/02/21 12:32:57 by averin           ###   ########.fr       */
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
	print_status(philo, "is sleeping");
	set_status(philo, SLEEP);
	usleep(param.time_to_sleep * 1000);
}

static void	do_eat(t_philo *philo, t_param param)
{
	print_status(philo, "is thinking");
	set_status(philo, THINK);
	// if (philo->number % 2)
	// {
		printf("* %d left fork status=%d\n", philo->number, get_var(philo->left_fork));
		while (get_var(philo->left_fork) != 0)
			;
		set_var(philo->left_fork, philo->number);
		print_status(philo, "has taken left fork");
		printf("* %d right fork status=%d\n", philo->number, get_var(philo->right_fork));
		while (get_var(philo->right_fork) != 0)
			;
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
			do_sleep(philo, philo->data->param);
		// }
		// else
		// {
		// 	do_sleep(philo, philo->data->param);
		// 	do_eat(philo, philo->data->param);
		// }
	}
	print_status(philo, "has finished");
	return (0);
}
