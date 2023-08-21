//
// Created by syluiset on 6/25/23.
//

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
//Bonus
# include <stdbool.h>

// typedef enum e_state
// {
// 	begin
// 	think
// 	eat
// 	sleep
// }				t_state;

typedef struct s_data
{
	struct timeval	time_start;
	size_t			nb_of_philosophers;
	int				time_to_die; // en millisecond
	int				time_to_eat;	// en millisecond
	int				time_to_sleep;// en millisecond
	int				nb_must_eat;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	int				*p_array;
}				t_data;

/*utils*/
int		ft_atoi(const char *nptr);

/*begin*/
t_data	*parsing_arg(int argc, char **argv);
int		create_thread(t_data *data);

void	*choose_routine(void *data);
#endif
