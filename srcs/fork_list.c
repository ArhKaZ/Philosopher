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

static int	count_fork(t_fork_list *lst)
{
	int count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_fork_list	*new_fork(t_fork_list *lst)
{
	t_fork_list	*new;

	new = malloc(sizeof(t_fork_list));
	new->number = count_fork(lst);
	new->mutex = pthread_mutex_init(&(new->mutex));
	new->next = NULL;
	return (new);
}

void	fork_add_back(t_fork **forks, t_fork_list *new)
{
	if (forks->first && forks->last)
	{
		forks->last->next = new;
		forks->last = new;
	}
	else
	{
		forks->first = new;
		forks->last = new;
	}
}