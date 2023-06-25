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


 pthread_mutex_t m1;
pthread_mutex_init(&m1, NULL);
pthread_mutex_lock(&m1);
pthread_mutex_unlock(&m1);
phtread_mutex_destroy(&m1);


void	print_info(t_data_philo *philo)
{
	printf("%ld\n", philo->nb_of_philosophers);
	printf("%ld\n", philo->nb_of_fork);
	printf("%d\n", philo->nb_must_eat);
	printf("%d\n", philo->time_to_sleep);
	printf("%d\n", philo->time_to_eat);
	printf("%d\n", philo->time_to_die);
}

int	main(int argc, char **argv)
{
	t_data_philo	*philo;
	if (argc != 5 && argc != 6)
		return (printf("Not enough arguments"), 1);
	philo = parsing_philo(argv);
	print_info(philo);
	create_thread(philo);
	free(philo);
	return (0);
}