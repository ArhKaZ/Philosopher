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

void	actions_thread(t_data_philo *philo)
{
	t_philo_list	*new_p;
	t_fork_list		*new_f;

	new_p = create_philo(count_philo(philo->philos->first));
	philo_add_back(&(philo->philos), new_p);
	new_f = new_fork(philo->forks->first);
	fork_add_back(&(philo->forks), new_f);
}

static int	join_thread(t_data_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->nb_of_philosophers)
	{
		if (pthread_join(p, NULL))
		{
			printf("join failed");
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_thread(t_data_philo *philo)
{
	pthread_t	thread[philo->nb_of_philosophers];
	int			i;

	i = 0;
	while (i < philo->nb_of_philosophers)
	{
		if (pthread_create(&thread[i], NULL, actions_thread, (void *)philo) != 0)
		{
			printf("Failed create");
			return (1);
		}
		i++;
	}
	join_thread(philo);
	return (0);
}

t_data_philo	*parsing_philo(char **argv) // ? Securiser si negatif ?
{
	t_data_philo	*new;

	new = malloc(sizeof(t_data_philo));
	new->nb_of_philosophers = ft_atoi(argv[1]);
	new->nb_of_fork = new->nb_of_philosophers;
	new->time_to_die = ft_atoi(argv[2]);
	new->time_to_eat = ft_atoi(argv[3]);
	new->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		new->nb_must_eat = ft_atoi(argv[5]);
	else
		new->nb_must_eat = -1;
	new->philos = NULL;
	new->act_philo = 0;
	return (new);
}