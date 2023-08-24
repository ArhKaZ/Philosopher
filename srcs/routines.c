/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:27:24 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/24 16:13:38 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosopher.h"


long	get_time_in_mlsc(struct timeval time_start, struct timeval time_now)
{
	return ((time_now.tv_sec * 1000 + time_now.tv_usec / 1000)
		- (time_start.tv_sec * 1000 + time_start.tv_usec / 1000));
}

int p_eating(t_data_p *data)
{
	pthread_mutex_lock(data->fork_left);
	print_output(OUT_FORK, data);
	pthread_mutex_lock(data->fork_right);
	print_output(OUT_FORK, data);
	print_output(OUT_EAT, data);
	usleep(data->base_data->time_to_eat * 1000);
	pthread_mutex_unlock(data->fork_right);
	pthread_mutex_unlock(data->fork_left);
	return (0);
}

int p_sleeping(t_data_p *data)
{
	print_output(OUT_SP, data);
	usleep(data->base_data->time_to_sleep * 1000);
	return (0);
}

int p_thinking(t_data_p *data)
{
	print_output(OUT_TK, data);
	return (0);
}

void    *choose_routine(void *arg)
{
	struct timeval	time_now;
	t_data_p		*data;

	data = (t_data_p *)arg;
	pthread_mutex_lock(&data->base_data->m_global);
	gettimeofday(&time_now, NULL);
	printf("%ld %ld %s\n", get_time_in_mlsc(data->base_data->time_start, time_now), data->position_p, OUT_TK);
	pthread_mutex_unlock(&data->base_data->m_global);
	while (1)
	{
		pthread_mutex_lock(&data->base_data->m_global);
		if (data->base_data->philo_is_dead == false && data->base_data->all_philo_are_fulled == false)
		{
			pthread_mutex_unlock(&data->base_data->m_global);
			break ;
		}
		pthread_mutex_unlock(&data->base_data->m_global);
		if (data->base_data->nb_of_philosophers > 1)
		{
			p_eating(data);
			p_sleeping(data);
			p_thinking(data);
		}
	}
	return (0);
}
