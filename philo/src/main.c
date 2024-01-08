/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:58:01 by averin            #+#    #+#             */
/*   Updated: 2024/01/06 16:21:50 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define TIMES_TO_COUNT 21000

void	*test(void *arg)
{
	int	i;
	int	*j = (int *) arg;

	(void)arg;
	i = -1;
	while (++i < TIMES_TO_COUNT)
	{
		(*j)++;
		// printf("hello for the %dth time\n", *j);
		// usleep(1000000);
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	pthread_t		thread;
	pthread_t		threadt;
	pthread_mutex_t	mutex;
	int				i;
	int				j;

	(void)argc;
	(void)argv;
	// if (argc < 5 || argc > 6)
	// 	return (printf(ERROR_USAGE, argv[0]), 1);
	i = -1;
	j = 0;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread, NULL, &test, &j);
	pthread_create(&threadt, NULL, &test, &j);
	// printf("Hello from parent\n");
	pthread_join(thread, NULL);
	pthread_join(threadt, NULL);
	pthread_mutex_destroy(&mutex);
	printf("parent ended %d\n", j);
	return (0);
}
