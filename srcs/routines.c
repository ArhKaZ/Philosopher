/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:27:24 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/25 19:06:12 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosopher.h"

int	p_eating(t_data_p *data)
{
	if (data->position_p % 2 == 1)
	{
		pthread_mutex_lock(data->fork_left);
		print_output(OUT_FORK, data);
		pthread_mutex_lock(data->fork_right);
		print_output(OUT_FORK, data);
	}
	else
	{
		pthread_mutex_lock(data->fork_right);
		print_output(OUT_FORK, data);
		pthread_mutex_lock(data->fork_left);
		print_output(OUT_FORK, data);
	}
	print_output(OUT_EAT, data);
	usleep((data->base_data->time_to_eat * 1000) * 80 / 100);
	usleep((data->base_data->time_to_eat * (5 / 100)) * 1000);
	usleep((data->base_data->time_to_eat * (5 / 100)) * 1000);
	usleep((data->base_data->time_to_eat * (5 / 100)) * 1000);
	usleep((data->base_data->time_to_eat * (5 / 100)) * 1000);
	pthread_mutex_unlock(data->fork_right);
	pthread_mutex_unlock(data->fork_left);
	return (0);
}

int	p_sleeping(t_data_p *data)
{
	print_output(OUT_SP, data);
	usleep((data->base_data->time_to_sleep * 1000) * 80 / 100);
	usleep((data->base_data->time_to_sleep * 1000) * 5 / 100);
	usleep((data->base_data->time_to_sleep * 1000) * 5 / 100);
	usleep((data->base_data->time_to_sleep * 1000) * 5 / 100);
	usleep((data->base_data->time_to_sleep * 1000) * 5 / 100);
	return (0);
}

int	checking_status(t_data_p *data)
{
	pthread_mutex_lock(&data->base_data->m_global);
	if (data->base_data->philo_is_dead == true || 
		data->base_data->all_philo_are_fulled == true)
	{
		pthread_mutex_unlock(&data->base_data->m_global);
		return (1);
	}
	return (0);
}

void	*choose_routine(void *arg)
{
	struct timeval	time_now;
	t_data_p		*data;

	data = (t_data_p *)arg;
	pthread_mutex_lock(&data->base_data->m_global);
	gettimeofday(&time_now, NULL);
	printf("%ld %ld %s\n", get_time_in_ms(data->base_data->time_start, time_now),
		data->position_p, OUT_TK);
	pthread_mutex_unlock(&data->base_data->m_global);
	while (1)
	{
		if (checking_status(data))
			break ;
		pthread_mutex_unlock(&data->base_data->m_global);
		if (data->base_data->nb_of_philosophers > 1)
		{
			p_eating(data);
			p_sleeping(data);
			print_output(OUT_TK, data);
		}
	}
	return (0);
}

// int	p_thinking(t_data_p *data)
// {
//	print_output(OUT_TK, data);
// 	return (0);
// }