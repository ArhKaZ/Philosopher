

int	create_thread(t_data *data)
{
	size_t		i;
	t_data_p	*data_array_p;

	i = 0;
	data_array_p = malloc(sizeof(t_data_p) * (data->nb_of_philosophers));
	if (!data_array_p)
		return (1);
	pthread_mutex_lock(&data->m_global);
	while (i < data->nb_of_philosophers)
	{
		get_data_for_philo(data, i, &data_array_p[i]);
		if (!(&data_array_p[i])) {
			pthread_mutex_unlock(&data->m_global);
			return (/* clean */ 1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->m_global);
	i = 0;
	while (i < data->nb_of_philosophers)
	{
		if (pthread_create(&data->philo[i], NULL, &choose_routine, (void *)&data_array_p[i]) != 0)
		{
			printf("Create failed");
			return (1);
		}
		i++;
	}
	data->table = data_array_p;
	return (0);
}

int	join_thread(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_of_philosophers)
	{
		if (pthread_join(data->philo[i], NULL))
		{
			dprintf(2, "2\n");
			pthread_mutex_unlock(&data->m_global);
			return (1);
		}
		i++;

	}
	return (0);
}

void	get_data_for_philo(t_data *base_data, size_t position, t_data_p *data)
{
	data->base_data = base_data;
	data->position_p = position + 1;
	if (position == 0)
		data->fork_left = &base_data->fork[base_data->nb_of_philosophers - 1];
	else
		data->fork_left = &base_data->fork[position - 1];
	data->fork_right = &base_data->fork[position];
	data->nb_meal = 0;
	gettimeofday(&data->time_last_meal, NULL);
}

t_data	*parsing_arg(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	gettimeofday(&data->time_start, NULL);
	data->nb_of_philosophers = ft_atoi(argv[1]); // plus d'un philo et temps > 60 et (temps die > 120)
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_must_eat = ft_atoi(argv[5]);
	else
		data->nb_must_eat = -1;
	data->philo = malloc(sizeof(pthread_t) * (data->nb_of_philosophers));
	if (!data->philo)
		return (NULL);
	data->fork = malloc(sizeof(pthread_mutex_t) * (data->nb_of_philosophers));
	if (!data->fork)
		return (NULL);
	data->all_philo_are_fulled = false;
	data->philo_is_dead = false;
	return (data);
}