/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:54:19 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/25 19:21:29 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosopher.h"

int	clean_mutex(t_data *data, size_t loc)
{
	size_t	i;

	i = 0;
	while (i < loc)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	return (0);
}

int	create_fork(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_of_philosophers)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL))
			return (clean_mutex(data, i), 1);
		i++;
	}
	if (pthread_mutex_init(&data->m_global, NULL))
		return (clean_mutex(data, i), 1);
	return (0);
}
