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



 /* exemple thread

 	void *roll_dice()
 	{
 		int value = (rand());
 		int *result = malloc(sizeof(int));
 		*result = value;
 		return (void *) result;
 	}
 	int *res;
	pthread_t t1;
	if (pthread_create(&t1, NULL, &roll_dice, NULL) != 0)
		return (1) ERROR
	if (pthread_join(t1, &res) != 0); wait for thread (NULL est pour stocker la valeur de retour)
		return (1) ERROR
 	free(res);
	*/


//  pthread_mutex_t m1;
// pthread_mutex_init(&m1, NULL);
// pthread_mutex_lock(&m1);
// pthread_mutex_unlock(&m1);
// phtread_mutex_destroy(&m1);

void	free_data(t_data *data)
{
	size_t i;

	i = 0;
	while (i < data->nb_of_philosophers)
	{
		pthread_mutex_destroy(&data->fork[i]);
		free(&data->table[i]);
		i++;
	}
	pthread_mutex_destroy(&data->m_global);
	pthread_mutex_destroy(&data->m_print);
	free(data->fork);
	free(data->philo);
	free(data);
}

void	print_info(t_data *philo)
{
	printf("%ld\n", philo->nb_of_philosophers);
	printf("%d\n", philo->time_to_die);
	printf("%d\n", philo->time_to_eat);
	printf("%d\n", philo->time_to_sleep);
	printf("%d\n", philo->nb_must_eat);
}

int	check_dead(t_data_p *data)
{
	struct timeval time_now;

	pthread_mutex_lock(&data->base_data->m_global);
	gettimeofday(&time_now, NULL);
	if (get_time_in_mlsc(data->time_last_meal, time_now) > data->base_data->time_to_die)
	{
		printf("%ld %ld %s\n", get_time_in_mlsc(data->base_data->time_start, time_now), data->position_p, OUT_DTH);
		data->base_data->philo_is_dead = true;
		pthread_mutex_unlock(&data->base_data->m_global);
		return (1);
	}
	pthread_mutex_unlock(&data->base_data->m_global);
	return (0);
}

int	check_philo_are_fulled(t_data_p *data, int i)
{
	static size_t	count = 0;

	if (i == 0)
		count = 0;
	pthread_mutex_lock(&data->base_data->m_global);
	if (data->base_data->nb_must_eat == -1)
	{
		pthread_mutex_unlock(&data->base_data->m_global);
		return (0);
	}
	if (data->nb_meal >= data->base_data->nb_must_eat)
		count = count + 1;
	if (count == data->base_data->nb_of_philosophers)
	{
		data->base_data->all_philo_are_fulled = true;
		pthread_mutex_unlock(&data->base_data->m_global);
		return (1);
	}
	pthread_mutex_unlock(&data->base_data->m_global);
	return (0);
}

int	check_dead_or_full(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_of_philosophers)
	{
		if (check_dead(&data->table[i]))
			return (1);
		if (check_philo_are_fulled(&data->table[i], i))
			return (1);
		i++;
		if (i == data->nb_of_philosophers)
			i = 0;
	}
	return (0);
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
	//if (check_error_arg(argc, argv))
		//return (printf("error with arguments\n"));
	philo = parsing_arg(argc, argv);
	if (!philo)
		return (1);
	create_fork(philo);
	create_thread(philo);
	check_dead_or_full(philo);
	join_thread(philo);
	//free_data(philo);
	return (0);
}