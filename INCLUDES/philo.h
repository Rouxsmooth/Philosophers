/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:39:40 by mzaian            #+#    #+#             */
/*   Updated: 2025/04/01 18:17:22 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int	is_alive;
	int	eats;
	int	thinks;
	int	sleeps;
	int	has_eaten;
	int	has_thought;
	int	has_slept;
}	t_philo;

typedef struct s_time
{
	struct timeval	tv;
	long int		start_time;
	long int		curr_time;
}	t_time;

typedef struct s_vals
{
	int		t2eat;
	int		t2die;
	int		t2sleep;
	int		philos_amount;
	// int		eat_amount;
	int		*forks;
	t_time	time;
	t_philo	*philos;
}	t_vals;

/* ternaries */
void	*ft_ternary(void *output1, void *output2, int condition);
int		ft_intternary(int i1, int i2, int condition);

#endif