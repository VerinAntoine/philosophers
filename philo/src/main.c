/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:58:01 by averin            #+#    #+#             */
/*   Updated: 2024/02/26 10:26:48 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_param param, t_fork **forks)
{
	int	i;

	*forks = ft_calloc(param.philo_number, sizeof(t_fork));
	if (!*forks)
		return (EMEM);
	i = -1;
	while (++i < param.philo_number)
		init_var(&(*forks)[i], 0);
	return (0);
}

void	monitor_philos(t_param param, t_philo *philo)
{
	int	i;
	int	finished;

	while (get_var(&philo->data->state) == RUNNING)
	{
		i = -1;
		finished = 1;
		while (++i < param.philo_number)
		{
			if (param.eat_number == -1
				|| get_var(&philo[i].eat_count) < param.eat_number)
				finished = 0;
		}
		if (finished)
		{
			set_var(&philo[0].data->state, STOPED);
			return ;
		}
		usleep(1);
	}
}

void	wait_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->param.philo_number)
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
	init_forks(data.param, &forks);
	data.start = get_miliseconds();
	setup_philo(&data, forks, &philos);
	set_var(&data.state, RUNNING);
	monitor_philos(data.param, philos);
	wait_threads(&data, philos);
	pthread_mutex_destroy(&data.write);
	pthread_mutex_destroy(&data.state.mutex);
	clean_philo(philos, forks, data.param);
	return (0);
}
