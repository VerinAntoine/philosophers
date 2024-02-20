/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:58:01 by averin            #+#    #+#             */
/*   Updated: 2024/02/20 13:30:04 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_miliseconds(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf("! time error\n"), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// TODO: may need to check calculous for left fork
int	setup_philo(t_data *data, t_fork *forks, t_philo **philos)
{
	int	i;

	*philos = ft_calloc(data->param.philo_number, sizeof(t_philo));
	if (!*philos)
		return (EMEM);
	i = -1;
	while (++i < data->param.philo_number)
	{
		(*philos)[i].number = i;
		(*philos)[i].data = data;
		(*philos)[i].right_fork = &(forks[i]);
		(*philos)[i].left_fork = &(forks[i % data->param.philo_number]);
		pthread_mutex_init(&(*philos)[i].status.mutex, NULL);
		if (pthread_create(&(*philos)[i].thread, NULL, &philo_routine,
				&(*philos)[i]) == -1)
			return (perror("thread"), EGEN);
	}
	return (0);
}

int	init_forks(t_param param, t_fork **forks)
{
	int	i;

	*forks = ft_calloc(param.philo_number, sizeof(t_fork));
	if (!*forks)
		return (EMEM);
	i = -1;
	while (++i < param.philo_number)
		pthread_mutex_init(&(*forks)[i].mutex, NULL);
	return (0);
}

void	wait_threads(t_param param, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < param.philo_number)
		pthread_join(philos[i].thread, NULL);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philos;
	t_fork	*forks;

	if (argc < 5 || argc > 6)
		return (printf(ERROR_USAGE, argv[0]), 1);
	if (!parse_params(argv + 1, &data.param))
		return (printf(ERROR_USAGE, argv[0]), 1);
	pthread_mutex_init(&data.write, NULL);
	init_var(&data.state, WAITING);
	print_params(data.param);
	init_forks(data.param, &forks);
	setup_philo(&data, forks, &philos);
	set_var(&data.state, RUNNING);
	// WATCH PHILOS
	wait_threads(data.param, philos);
	return (0);
}
