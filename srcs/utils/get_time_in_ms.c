/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_in_ms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:52:45 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/25 19:07:36 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/philosopher.h"

long	get_time_in_ms(struct timeval time_start, struct timeval time_now)
{
	return ((time_now.tv_sec * 1000 + time_now.tv_usec / 1000)
		- (time_start.tv_sec * 1000 + time_start.tv_usec / 1000));
}
