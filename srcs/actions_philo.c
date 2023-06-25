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

void	change_status_for_eat(t_data_philo *data)
{
	data->philos->first->state = eat;

}

