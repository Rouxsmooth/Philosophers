/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternaries.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:48:30 by mzaian            #+#    #+#             */
/*   Updated: 2025/04/01 16:57:51 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	*ft_ternary(void *output1, void *output2, int condition)
{
	if (condition)
		return (output1);
	return (output2);
}

int	ft_intternary(int i1, int i2, int condition)
{
	if (condition)
		return (i1);
	return (i2);
}
