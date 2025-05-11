/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printmessages.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:39:15 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/11 19:53:40 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	ft_putstr_fd(char *output, int fd)
{
	int	i;

	i = 0;
	while (output[i])
		i++;
	write(fd, output, i);
	return ;
}

int	display_error(char *output)
{
	return (ft_putstr_fd("\e[31mError: ", 2), ft_putstr_fd(output, 2),
		ft_putstr_fd("\n\e[0m", 2), -1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;;
	}
	return (*s1 - *s2);
}

int messages(int philo, long int time, const char *rule)
{
	if (ft_strcmp(rule, "eat") == 0)
		return (printf("%6ld - %3d is eating\n", time, philo + 1));
	else if (ft_strcmp(rule, "sleep") == 0)
		return (printf("%6ld - %3d is sleeping\n", time, philo + 1));
	else if (ft_strcmp(rule, "think") == 0)
		return (printf("%6ld - %3d is thinking\n", time, philo + 1));
	else if (ft_strcmp(rule, "fork") == 0)
		return (printf("%6ld - %3d has taken a fork\n", time, philo + 1));
	else if (ft_strcmp(rule, "die") == 0)
		return (printf("%6ld - %3d died\n", time, philo + 1));
	return (1);
}

void	print_philo_vals(t_philo *philo)
{
	printf("{philo %p -> (F1 %d), (F2 %d), (has_eaten %d), (has_slept %d), \
(is_alive %d), (thinks %d), (thread %lu)}\n",
	philo, philo->fork1, philo->fork2, philo->has_eaten, philo->has_slept,
	philo->is_alive, philo->thinks,	philo->thread);
	return ;
}
