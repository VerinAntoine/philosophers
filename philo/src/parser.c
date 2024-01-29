/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:15:17 by averin            #+#    #+#             */
/*   Updated: 2024/01/09 13:29:59 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_params(char **argv, t_param *params)
{
	params->philo_number = ft_atoi(argv[0]);
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
