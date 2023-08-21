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
	t_data *data;

	data = malloc(sizeof(t_data));
	data->nb_of_philosophers = ft_atoi(argv[1]);
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
	gettimeofday(&data->time_start ,NULL);
	data->p_array = malloc(sizeof(int) * data->nb_of_philosophers);
	return (data);
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

int	create_fork(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_of_philosophers)
	{
		pthread_mutex_init(&(data->fork[i]), NULL);
		i++;
	}
	return (0);
}

void	*crt_thr(void *data)
{
	printf("ccc\n");
	(void)data;
	return (NULL);
}

int	create_thread(t_data *data)
{
	size_t		i;

	i = 0;
	while (i < data->nb_of_philosophers)
	{
		if (pthread_create(&data->philo[i], NULL, choose_routine, (void *)data) != 0)
		{
			printf("Create failed");
			return (1);
		}
		i++;
	}
	if (join_thread(data))
		return (1);
	create_fork(data);
	return (0);
}