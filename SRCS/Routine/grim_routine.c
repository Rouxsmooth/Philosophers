/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:10:08 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/14 16:14:34 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	find_new_prey(t_grim grim)
{
	int	i;
	int	prey;
	
	i = 0;
	prey = 0;
	while (i < grim.prey_amount)
	{
		if (grim.id_log[i] < prey)
			prey = grim.id_log[i];
		i++;
	}
	grim.hunting_down = prey;
	return ;
}

void	grim_reaper_routine(void *arg)
{
	
}
