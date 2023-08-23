/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:53:51 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/23 12:56:43 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosopher.h"

void	print_output(char *print, t_data_p *data, struct timeval time)
{
    size_t is_dead;

    is_dead = data->base_data->philo_is_dead;
    if (is_dead == 0 || data->position_p == is_dead)
    {
        pthread_mutex_lock(&data->base_data->m_print);
        printf("%ld %ld %s\n", get_time_in_mlsc(data->base_data->time_start, time), data->position_p, print);
        pthread_mutex_unlock(&data->base_data->m_print);
    }
}