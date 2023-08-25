/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_on_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:54:37 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/25 19:20:27 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosopher.h"

void	compose_table(t_data *data, t_data_p *table)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&data->m_global);
	while (i < data->nb_of_philosophers)
	{
		get_data_for_philo(data, i, &table[i]);
		if (!(&table[i])) 
		{
			pthread_mutex_unlock(&data->m_global);
			return ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->m_global);
}

int	create_thread(t_data *data)
{
	size_t		i;
	t_data_p	*table;

	i = 0;
	table = malloc(sizeof(t_data_p) * (data->nb_of_philosophers));
	if (!table)
		return (1);
	compose_table(data, table);
	while (i < data->nb_of_philosophers)
	{
		if (pthread_create(&data->philo[i], NULL, 
				&choose_routine, (void *)&table[i]) != 0)
		{
			printf("Create failed");
			return (1);
		}
		i++;
	}
	data->table = table;
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
	if (!data)
		return (NULL);
	gettimeofday(&data->time_start, NULL);
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
	data->all_philo_are_fulled = false;
	data->philo_is_dead = false;
	return (data);
}
