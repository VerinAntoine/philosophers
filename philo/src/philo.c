/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:26:14 by averin            #+#    #+#             */
/*   Updated: 2024/02/26 11:13:29 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_starving(t_philo *philo, t_param param)
{
	return (get_miliseconds() - philo->last_eat > param.time_to_die);
}

void	clean_philo(t_philo *philos, t_fork *forks, t_param param)
{
	int	i;

	i = -1;
	while (++i < param.philo_number)
	{
		pthread_mutex_destroy(&philos[i].status.mutex);
		pthread_mutex_destroy(&philos[i].eat_count.mutex);
		pthread_mutex_destroy(&forks[i].mutex);
	}
	free(philos);
	free(forks);
}

int	setup_philo(t_data *data, t_fork *forks, t_philo **philos)
{
	int	i;

	*philos = ft_calloc(data->param.philo_number, sizeof(t_philo));
	if (!*philos)
		return (EMEM);
	i = -1;
	while (++i < data->param.philo_number)
	{
		(*philos)[i].number = i + 1;
		(*philos)[i].data = data;
		(*philos)[i].right_fork = &(forks[i]);
		(*philos)[i].left_fork = &(forks[(i + 1) % data->param.philo_number]);
		init_var(&(*philos)[i].status, 0);
		init_var(&(*philos)[i].eat_count, 0);
		if (pthread_create(&(*philos)[i].thread, NULL, &philo_routine,
			&(*philos)[i]) == -1)
			return (perror("thread"), EGEN);
	}
	return (0);
}
