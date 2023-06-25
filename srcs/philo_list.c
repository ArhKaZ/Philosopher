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

int	count_philo(t_philo_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_philo_list	*create_philo(int count_philo)
{
	t_philo_list	*new;

	new = malloc(sizeof(t_philo_list));
	if (!new)
		return (NULL);
	new->number = count_philo + 1;
	new->next = NULL;
	new->state = begin;
	return (new);
}

void	philo_add_back(t_philo **philos, t_philo_list *new)
{
	if (philos->first && philos->last)
	{
		philos->last->next = new;
		philos->last = new;
	}
	else
	{
		philos->first = new;
		philos->last = new;
	}
}