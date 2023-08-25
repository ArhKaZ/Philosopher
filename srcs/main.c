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

void	free_data(t_data *data, int clean_f)
{
	size_t	i;

	i = 0;
	if (clean_f == 1)
	{
		while (i < data->nb_of_philosophers)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&data->m_global);
	free(data->fork);
	free(data->philo);
	free(data);
}

int	check_error_arg(int argc, char **argv)
{
	int	i;
	int	*tab;
	int	ret;

	ret = 0;
	tab = malloc(sizeof(int) * argc - 1);
	if (!tab)
		return (1);
	i = 1;
	while (i < argc)
	{
		tab[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	if (tab[0] < 1 || tab[1] < 60 || tab[2] < 60 || tab[3] < 60 || 
		(argc == 6 && tab[4] < 1))
		ret = 1;
	free(tab);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_data		*philo;

	if (argc != 5 && argc != 6)
		return (printf("Not has the right number of arguments"), 1);
	if (check_error_arg(argc, argv))
		return (printf("error with arguments\n"));
	philo = parsing_arg(argc, argv);
	if (!philo)
		return (1);
	if (create_fork(philo))
		return (free_data(philo, 0), 1);
	if (create_thread(philo))
		return (free_data(philo, 1), 1);
	check_dead_or_full(philo);
	join_thread(philo);
	free(philo->table);
	free_data(philo, 1);
	return (0);
}
