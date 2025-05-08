
int	take_fork(t_vals *vals, int fork, int currtime, int currphilo)
{
	if (!vals->forks_usage[fork])
		return (0);
	pthread_mutex_lock(&vals->forks[fork]);
	messages(currphilo, currtime, "fork");
	vals->forks_usage[fork] = 0;
	return (1);
}

void	need2eat(t_vals *vals, t_philo *philo, int currphilo)
{
	long int	currtime;
	int			fork1;
	int			fork2;
	
	currtime = get_utime((&vals->time));
	fork1 = currphilo;
	fork2 = (currphilo + 1) % vals->philos_amount;
	if (fork1 > fork2)
	{
		fork1 ^= fork2;
		fork2 ^= fork1;
		fork1 ^= fork2;
	}
	if (take_fork(vals, fork1, currtime, currphilo))
		philo->fork1 = fork1;
	if (take_fork(vals, fork2, currtime, currphilo))
		philo->fork2 = fork2;
	if (philo->fork1 != -1 && philo->fork2 != -1)
	{
		messages(currphilo, currtime, "eat");
		philo->has_eaten = 1;
		philo->thinks = -1;
		usleep(vals->t2eat);
	}
	return ;
}

void	set2sleep(t_vals *vals, t_philo *philo, int currphilo)
{
	long int	sleeptime;

	sleeptime = get_utime(&(vals->time));
	messages(currphilo, sleeptime, "sleep");
	pthread_mutex_unlock(&(vals->forks[philo->fork1]));
	pthread_mutex_unlock(&(vals->forks[philo->fork2]));
	philo->fork1 = -1;
	philo->fork2 = -1;
	philo->thinks = -1;
	print_philo_vals(philo);
	return ;
}

int	check_dead_philo(t_vals *vals, t_philo *philo)
{
	if (!vals->philo_died)
		return (0);
	if (philo->fork1 != -1)
		pthread_mutex_unlock(&(vals->forks[philo->fork1]));
	if (philo->fork2 != -1)
		pthread_mutex_unlock(&(vals->forks[philo->fork2]));
	return (1);
}

void	*philo_routine(void *arg)
{
	t_context	ctx;
	t_philo		philo;

	ctx = *(t_context *)arg;
	philo = ctx.vals->philos[ctx.id];
	//printf("philo id%d, philo is %s \n", ctx.id, ctx.vals->philo_died ? "dead" : "alive");
	if (check_dead_philo(ctx.vals, &philo))
		return (NULL);
	gettimeofday(&ctx.vals->time.tv, NULL);
	ctx.vals->time.start_time = ctx.vals->time.tv.tv_usec;
	//print_philo_vals(&philo);
	while (philo.is_alive)
	{
		if (philo.thinks != -1 && !philo.has_eaten)
			need2eat(ctx.vals, &philo, ctx.id);
		if (philo.thinks != -1 && !philo.has_eaten)
		{
			
			usleep()
		}
		if (!philo.is_alive)
			break ;
	}
	messages(ctx.id, get_utime(&(ctx.vals->time)), "die");
	ctx.vals->philo_died = 1;
	return (NULL);
}
