/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:27:24 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/22 17:21:17 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosopher.h"
// include <sys/time.h>
// #include <stdio.h>
 
// int main() {
 
//   struct timeval start, end;
//   gettimeofday(&start, NULL);
 
//   for (int i = 0; i <1e5 ; i++) {
//   }
 
//   gettimeofday(&end, NULL);
//   printf("Time taken to count to 10^5 is : %ld micro seconds\n",
//     ((end.tv_sec * 1000000 + end.tv_usec) -
//     (start.tv_sec * 1000000 + start.tv_usec)));

//   return 0;
// }

long	get_time_in_mlsc(struct timeval time_start, struct timeval time_now)
{
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000) - (time_start.tv_sec * 1000 + time_start.tv_usec / 1000);
}

int p_eating(t_data_p *data)
{
    struct timeval time_start_eating;
	struct timeval time_now;

	pthread_mutex_lock(data->fork_left);
	pthread_mutex_lock(data->fork_right);
	gettimeofday(&time_start_eating, NULL);
	print_output(OUT_FORK, data, time_start_eating);
	gettimeofday(&time_start_eating, NULL);
	print_output(OUT_FORK, data, time_start_eating);
	gettimeofday(&time_start_eating, NULL);
	print_output(OUT_EAT, data, time_start_eating);
	gettimeofday(&time_now, NULL);
	while (get_time_in_mlsc(data->base_data->time_start, time_now) -
	get_time_in_mlsc(data->base_data->time_start, time_start_eating) < data->base_data->time_to_eat)
		gettimeofday(&time_now, NULL);
	data->time_last_meal = time_now;
	pthread_mutex_unlock(data->fork_left);
	pthread_mutex_unlock(data->fork_right);
	return (0);
}

int p_sleeping(t_data_p *data)
{
	struct timeval	time_start_sleeping;
	struct timeval	time_now;

	gettimeofday(&time_start_sleeping, NULL);
	print_output(OUT_SP, data, time_start_sleeping);
	gettimeofday(&time_now, NULL);
	while (get_time_in_mlsc(data->base_data->time_start, time_now) - get_time_in_mlsc(data->base_data->time_start, time_start_sleeping) < data->base_data->time_to_sleep)
		gettimeofday(&time_now, NULL);
	return (0);
}

int p_thinking(t_data_p *data)
{
	struct timeval time_start_thinking;
    struct timeval time_now;

    gettimeofday(&time_start_thinking, NULL);
	print_output(OUT_TK, data, time_start_thinking);
	gettimeofday(&time_now, NULL);
	while (get_time_in_mlsc(data->base_data->time_start, time_now) - get_time_in_mlsc(data->base_data->time_start, time_start_thinking) < data->base_data->time_to_sleep)
		gettimeofday(&time_now, NULL);
	return (0);
}

void    *choose_routine(t_data_p *data)
{
	struct timeval	time_start_r;

	pthread_mutex_lock(&((t_data_p *)data)->base_data->m_global);
	gettimeofday(&time_start_r, NULL);
	print_output(OUT_TK, data, time_start_r);
	pthread_mutex_unlock(&((t_data_p *)data)->base_data->m_global);
	while (get_time_in_mlsc(((t_data_p *)data)->base_data->time_start, ((t_data_p *)data)->time_last_meal) < ((t_data_p *)data)->base_data->time_to_die)
	{
		p_eating(data);
		p_sleeping(data);
		p_thinking(data);
	}
	((t_data_p *)data)->base_data->m_global
	gettimeofday(&time_start_r, NULL);

	print_output(OUT_DTH, data, time_start_r);
    return (0);
}
