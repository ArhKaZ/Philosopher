//
// Created by syluiset on 6/25/23.
//

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>

typedef enum e_state
{
	begin
	think
	eat
	sleep
}				t_state;

typedef struct s_philo_list
{
	size_t				number;
	int					state;
	struct s_philo_list	next;
}				t_philo_list;

typedef struct s_philo
{
	t_philo_list	*first;
	t_philo_list	*last;
}				t_philo;

typedef struct s_fork_list
{
	int					number;
	pthread_mutex_t 	mutex;
	struct s_fork_list	*next;
}				t_fork_list;

typedef struct s_fork
{
	t_fork_list	*first;
	t_fork_list	*last;
}				t_fork;

typedef struct s_data_philo
{
	size_t			nb_of_philosophers;
	int				time_to_die; // en millisecond
	int				time_to_eat;	// en millisecond
	int				time_to_sleep;// en millisecond
	int				nb_must_eat;
	t_fork 			*forks;
	t_philo			*philos;
	int				act_philo;
}				t_data_philo;

/*utils*/
int		ft_atoi(const char *nptr);

/*begin*/
t_data_philo	*parsing_philo(char **argv);
int				create_thread(t_data_philo *philo);
/*philo_list*/
void			philo_add_back(t_philo **philos, t_philo_list *new);
t_philo_list	*create_philo(int count_philo);
int				count_philo(t_philo_list *lst);

/*forks*/
void			fork_add_back(t_fork **forks, t_fork_list *new);
t_fork_list		*new_fork(t_fork_list *lst);
#endif
