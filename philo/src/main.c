/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:58:01 by averin            #+#    #+#             */
/*   Updated: 2024/01/09 13:28:55 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_miliseconds()
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf("/!\\ time error\n"), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf(ERROR_USAGE, argv[0]), 1);
	if (!parse_params(argv + 1, &data.param))
		return (printf(ERROR_USAGE, argv[0]), 1);
	printf("philo_number: %d\n", data.param.philo_number);
	printf("time_to_die: %d\n", data.param.time_to_die);
	printf("time_to_eat: %d\n", data.param.time_to_eat);
	printf("time_to_sleep: %d\n", data.param.time_to_sleep);
	printf("eat_number: %d\n", data.param.eat_number);
	return (0);
}
