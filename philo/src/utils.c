/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:16:39 by averin            #+#    #+#             */
/*   Updated: 2024/01/09 13:30:48 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Transform a string to an int
 * @param  nptr string
 * @return int or -1 if error
 */
int	ft_atoi(const char *nptr)
{
	int	r;

	r = 0;
	if (*nptr == '\0')
		return (-1);
	while (*nptr)
	{
		if (!(*nptr >= '0' && *nptr <= '9'))
			return (-1);
		r *= 10;
		r += *nptr - '0';
		nptr++;
	}
	return (r);
}
