/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:15:17 by averin            #+#    #+#             */
/*   Updated: 2024/02/23 15:06:13 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_params(t_param param)
{
	printf("philo_number: %d\n", param.philo_number);
	printf("time_to_die: %d\n", param.time_to_die);
	printf("time_to_eat: %d\n", param.time_to_eat);
	printf("time_to_sleep: %d\n", param.time_to_sleep);
	printf("eat_number: %d\n", param.eat_number);
}

int	parse_params(char **argv, t_param *params)
{
	params->philo_number = ft_atoi(argv[0]);
	if (params->philo_number > 400)
		return (0);
	params->time_to_die = ft_atoi(argv[1]);
	params->time_to_eat = ft_atoi(argv[2]);
	params->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4])
		params->eat_number = ft_atoi(argv[4]);
	else
		params->eat_number = -1;
	return (params->philo_number != -1 && params->time_to_die != -1
		&& params->time_to_eat != -1 && params->time_to_sleep != -1
		&& (!argv[4] || params->eat_number != -1));
}
