/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:30:33 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/16 17:27:26 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosopher.h"

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

int	join_thread(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_of_philosophers)
	{
		if (pthread_join(data->philo[i], NULL))
		{
			printf("join failed");
			return (1);
		}
		i++;
	}
	return (0);
}

int	clean_mutex(t_data *data, size_t loc)
{
	size_t	i;

	i = 0;
	while (i < loc)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	return (0);
}

int	create_fork(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_of_philosophers)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL))
			return (clean_mutex(data, i), 1);
		i++;
	}
	if (pthread_mutex_init(&data->m_global, NULL))
		return (clean_mutex(data, i), 1);
	return (0);
}

int	create_thread(t_data *data)
{
	size_t		i;
	t_data_p	*data_array_p;

	i = 0;
	data_array_p = malloc(sizeof(t_data_p *) * (data->nb_of_philosophers));
	if (!data_array_p)
		return (1);
	pthread_mutex_lock(&data->m_global);
	while (i < data->nb_of_philosophers)
	{
		get_data_for_philo(data, i, &data_array_p[i]);
		if (!(&data_array_p[i]))
			return (/* clean */ 1);
		if (pthread_create(&data->philo[i], NULL, &choose_routine, (void *)&data_array_p[i]) != 0)
		{
			printf("Create failed");
			pthread_mutex_unlock(&data->m_global);
			return (1);
		}
		i++;
	}
	data->table = data_array_p;
	pthread_mutex_unlock(&data->m_global);
	return (0);
}