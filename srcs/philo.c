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

void	free_data(t_data *data)
{
	size_t i;

	i = 0;
	while (i < data->nb_of_philosophers)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
//    i = 0;
//    while (i < data->nb_of_philosophers)
//    {
//        free(&data->table[i]);
//        i++;
//    }
	pthread_mutex_destroy(&data->m_global);
	pthread_mutex_destroy(&data->m_print);
	free(data->fork);
	free(data->philo);
    free(data->table);
	free(data);
}

int	check_error_arg(int argc, char **argv)
{
	int	i;
	int	*tab;
	int	ret;

	ret = 0;
	tab = malloc(sizeof(int) * argc - 1);
	i = 1;
	while (i < argc)
	{
		tab[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	if (tab[0] < 1)
		ret = 1;
	if (tab[1] < 60)
		ret = 1;
	if (tab[2] < 60)
		ret = 1;
	if (tab[3] < 60)
		ret = 1;
	if (argc == 6 && tab[4] < 1)
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
	create_fork(philo);
	create_thread(philo);
	check_dead_or_full(philo);
	join_thread(philo);
	free_data(philo);
	return (0);
}

//105 800 200 200 philo meurt vite