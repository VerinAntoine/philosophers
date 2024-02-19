/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:21:54 by averin            #+#    #+#             */
/*   Updated: 2024/02/18 21:26:01 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_var(t_var *var, int val)
{
	pthread_mutex_init(&var->mutex, NULL);
	var->content = val;
}

void	set_var(t_var *var, int val)
{
	pthread_mutex_lock(&(var->mutex));
	var->content = val;
	pthread_mutex_unlock(&(var->mutex));
}

int	get_var(t_var *var)
{
	int	i;

	pthread_mutex_lock(&(var->mutex));
	i = var->content;
	pthread_mutex_unlock(&(var->mutex));
	return (i);
}
