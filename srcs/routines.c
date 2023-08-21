/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:27:24 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/21 18:36:50 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
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


int p_eating(t_data *data)
{
    struct timeval time_end;
    
    gettimeofday(&time_end, NULL);
    printf("%ld %ld has taken a fork\n",
        (time_end.tv_sec * 1000000 + time_end.tv_usec) - (data->time_start.tv_sec * 1000000 + data->time_start.tv_usec),
        data->nb_of_philosophers);
    printf("%ld %ld has taken a fork\n", (time_end.tv_sec * 1000000 + time_end.tv_usec) - (data->time_start.tv_sec * 1000000 + data->time_start.tv_usec), data->nb_of_philosophers);
    printf("%ld %ld is eating\n",(time_end.tv_sec * 1000000 + time_end.tv_usec) - (data->time_start.tv_sec * 1000000 + data->time_start.tv_usec), data->nb_of_philosophers);
    return (0);
}

int p_sleeping(t_data *data)
{   
    struct timeval time_end;

    gettimeofday(&time_end, NULL);
    printf("%ld %ld is sleeping\n", (time_end.tv_sec * 1000000 + time_end.tv_usec) - (data->time_start.tv_sec * 1000000 + data->time_start.tv_usec), data->nb_of_philosophers);    
    return (0);
}

int p_thinking(t_data *data)
{
    struct timeval time_end;

    gettimeofday(&time_end, NULL);
    printf("%ld %ld is thinking\n", (time_end.tv_sec * 1000000 + time_end.tv_usec) - (data->time_start.tv_sec * 1000000 + data->time_start.tv_usec), data->nb_of_philosophers);
    return (0);
}

void    *choose_routine(void *data)
{
    int i;

    i = 0;
    while (i < 40)
    {
        p_eating(data);
        p_sleeping(data);
        p_thinking(data);
        i++;
    }
    return (0);
}
