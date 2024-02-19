/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:58:01 by averin            #+#    #+#             */
/*   Updated: 2024/02/18 21:26:00 by averin           ###   ########.fr       */
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

int	setup_philo(t_data *data)
{
	int	i;

	init_var(&(data->state), WAITING);
	data->philos = ft_calloc(data->param.philo_number, sizeof(t_philo));
	data->forks = ft_calloc(data->param.philo_number, sizeof(t_fork));
	if (!data->philos || !data->forks)
		return (free(data->philos), free(data->forks), -1);
	i = -1;
	while (++i < data->param.philo_number)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		data->philos[i].number = i;
		data->philos[i].state = &(data->state);
		data->philos[i].left_fork = data->forks[i];
		data->philos[i].right_fork = data->forks[(i + 1)
			% data->param.philo_number];
		if (pthread_create(&(data->philos[i].thread), NULL, &philo_routine,
				&(data->philos[i])) == -1)
			return (perror("pthread"), -1);
	}
	set_var(&data->state, RUNNING);
	return (0);
}

void	wait_threads(t_data data)
{
	int	i;

	i = -1;
	while (++i < data.param.philo_number)
		pthread_join(data.philos[i].thread, NULL);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf(ERROR_USAGE, argv[0]), 1);
	if (!parse_params(argv + 1, &data.param))
		return (printf(ERROR_USAGE, argv[0]), 1);
	print_params(data.param);
	setup_philo(&data);
	wait_threads(data);
	return (0);
}
