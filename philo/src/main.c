/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:58:01 by averin            #+#    #+#             */
/*   Updated: 2024/01/09 13:02:55 by averin           ###   ########.fr       */
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

int	main(int argc, char const *argv[])
{
	if (argc < 5 || argc > 6)
		return (printf(ERROR_USAGE, argv[0]), 1);
	return (0);
}
