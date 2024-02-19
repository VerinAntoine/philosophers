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
	printf("[%ld] philo n %d waiting to start\n", get_miliseconds(),
		philo->number);
	while (get_var(philo->state) == WAITING)
		;
	printf("[%ld] %d finished waiting\n", get_miliseconds(), philo->number);
	return (0);
}
