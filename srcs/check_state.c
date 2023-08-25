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

int	check_dead(t_data_p *data)
{
	struct timeval time_now;

	pthread_mutex_lock(&data->base_data->m_global);
	gettimeofday(&time_now, NULL);
	if (get_time_in_mlsc(data->time_last_meal, time_now) > data->base_data->time_to_die)
	{
		printf("%ld %ld %s\n", get_time_in_mlsc(data->base_data->time_start, time_now), data->position_p, OUT_DTH);
		data->base_data->philo_is_dead = true;
		pthread_mutex_unlock(&data->base_data->m_global);
		return (1);
	}
	pthread_mutex_unlock(&data->base_data->m_global);
	return (0);
}

int	check_philo_are_fulled(t_data_p *data, size_t i)
{
	static size_t	count = 0;

	if (i == 0)
		count = 0;
	pthread_mutex_lock(&data->base_data->m_global);
	if (data->base_data->nb_must_eat == -1)
	{
		pthread_mutex_unlock(&data->base_data->m_global);
		return (0);
	}
	if (data->nb_meal >= data->base_data->nb_must_eat)
		count = count + 1;
	if (count == data->base_data->nb_of_philosophers)
	{
		data->base_data->all_philo_are_fulled = true;
		pthread_mutex_unlock(&data->base_data->m_global);
		return (1);
	}
	pthread_mutex_unlock(&data->base_data->m_global);
	return (0);
}

int	check_dead_or_full(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_of_philosophers)
	{
		if (check_dead(&data->table[i]))
			return (1);
		if (check_philo_are_fulled(&data->table[i], i))
			return (1);
		i++;
		if (i == data->nb_of_philosophers)
			i = 0;
	}
	return (0);
}