/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:53:51 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/24 15:26:56 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosopher.h"

void	print_output(char *print, t_data_p *data)
{
	size_t is_dead;
	struct timeval time;

	pthread_mutex_lock(&data->base_data->m_global);
	gettimeofday(&time, NULL);
	is_dead = data->base_data->philo_is_dead;
	if (is_dead == false && data->base_data->all_philo_are_fulled == false)
	{
		if (ft_strncmp(print, OUT_EAT, 10) == 0)
		{
			data->nb_meal++;
			data->time_last_meal = time;
		}
		printf("%ld %ld %s\n", get_time_in_mlsc(data->base_data->time_start, time), data->position_p, print);
	}
	pthread_mutex_unlock(&data->base_data->m_global);

}