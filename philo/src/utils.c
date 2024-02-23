/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:16:39 by averin            #+#    #+#             */
/*   Updated: 2024/02/23 15:06:29 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "limits.h"

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * Transform a string to an int
 * @param  nptr string
 * @return int or -1 if error
 */
int	ft_atoi(const char *nptr)
{
	long	r;

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
	if (r > INT_MAX || ft_strlen(nptr) > 11)
		return (-1);
	return (r);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*r;
	size_t			x;
	size_t			i;
	unsigned char	*p;

	x = nmemb * size;
	if (size != 0 && x / size != nmemb)
		return (NULL);
	r = malloc(nmemb * size);
	if (!r)
		return (NULL);
	p = r;
	i = -1;
	while (++i < nmemb * size)
		*p++ = 0;
	return (r);
}
