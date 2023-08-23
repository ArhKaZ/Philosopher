/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:27:24 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/23 13:15:04 by syluiset         ###   ########.fr       */
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

   // pthread_mutex_lock(&data->base_data->m_global);
	pthread_mutex_lock(data->fork_left);
	pthread_mutex_lock(data->fork_right);
	gettimeofday(&time_start_eating, NULL);
	print_output(OUT_FORK, data, time_start_eating);
	print_output(OUT_FORK, data, time_start_eating);
	gettimeofday(&time_start_eating, NULL);
	print_output(OUT_EAT, data, time_start_eating);
    data->nb_meal++;
    gettimeofday(&time_now, NULL);
    data->time_last_meal = time_now;
    usleep(data->base_data->time_to_eat * 1000);
	pthread_mutex_unlock(data->fork_left);
	pthread_mutex_unlock(data->fork_right);
  //  pthread_mutex_unlock(&data->base_data->m_global);
	return (0);
}

int p_sleeping(t_data_p *data)
{
	struct timeval	time_start_sleeping;
	struct timeval	time_now;

   // pthread_mutex_lock(&data->base_data->m_global);
	gettimeofday(&time_start_sleeping, NULL);
	print_output(OUT_SP, data, time_start_sleeping);
	gettimeofday(&time_now, NULL);
    usleep(data->base_data->time_to_sleep * 1000);
  //  pthread_mutex_unlock(&data->base_data->m_global);
	return (0);
}

int p_thinking(t_data_p *data)
{
	struct timeval time_start_thinking;
    struct timeval time_now;

   // pthread_mutex_lock(&data->base_data->m_global);
    gettimeofday(&time_start_thinking, NULL);
	print_output(OUT_TK, data, time_start_thinking);
	gettimeofday(&time_now, NULL);
   // pthread_mutex_unlock(&data->base_data->m_global);
	return (0);
}

int	check_philo_are_fulled(t_data *data)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (i < data->nb_of_philosophers)
	{
		if (data->nb_must_eat != -1 && data->table[i].nb_meal >= data->nb_must_eat)
			count++;
		if (count == data->nb_of_philosophers)
		{
			data->all_philo_are_fulled = true;
			return (0);
		}
		i++;
	}
	return (1);
}

void    *choose_routine(void *arg)
{
	struct timeval	time_now;
	t_data_p		*data;

	data = (t_data_p *)arg;
	pthread_mutex_lock(&data->base_data->m_global);
	gettimeofday(&time_now, NULL);
	print_output(OUT_TK, data, time_now);
	pthread_mutex_unlock(&data->base_data->m_global);
	while (get_time_in_mlsc(data->time_last_meal, time_now) < data->base_data->time_to_die && data->base_data->philo_is_dead == 0 && data->base_data->all_philo_are_fulled == false)
	{
        if (data->base_data->nb_of_philosophers > 1)
        {
            p_eating(data);
            p_sleeping(data);
            p_thinking(data);
        }
		check_philo_are_fulled(data->base_data);
        gettimeofday(&time_now, NULL);
	}
	if (!data->base_data->all_philo_are_fulled && data->base_data->philo_is_dead == 0)
	{
		data->base_data->philo_is_dead = data->position_p;
		gettimeofday(&time_now, NULL);
		print_output(OUT_DTH, data, time_now);
	}
    return (0);
}
