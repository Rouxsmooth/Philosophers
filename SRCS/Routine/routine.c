/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:48:21 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/11 20:28:04 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	*philo_routine(void *arg)
{
	t_context	ctx;
	t_mutexes	mutexes;
	t_philo		philo;

	ctx = *(t_context *)arg;
	mutexes = ctx.mutexes;
	pthread_mutex_lock(mutexes.philos);
	philo = ctx.vals->philos[ctx.id];
}