/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:58:11 by averin            #+#    #+#             */
/*   Updated: 2024/02/18 21:26:32 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	pthread_mutex_lock(&philo->data->write);
	printf("[%ld] philo n %d waiting to start\n", get_miliseconds(),
		philo->number);
	pthread_mutex_unlock(&philo->data->write);
	while (get_var(&philo->data->state) == WAITING)	
		;
	pthread_mutex_lock(&philo->data->write);
	printf("[%ld] %d finished waiting\n", get_miliseconds(), philo->number);
	pthread_mutex_unlock(&philo->data->write);
	return (0);
}
