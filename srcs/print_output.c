/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:53:51 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/22 17:01:50 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosopher.h"

void	print_output(char *print, t_data_p *data, struct timeval time)
{
	printf("%ld %ld %s\n", get_time_in_mlsc(data->base_data->time_start, time), data->position_p, print);
}