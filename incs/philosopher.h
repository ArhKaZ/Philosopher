/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:08:39 by syluiset          #+#    #+#             */
/*   Updated: 2023/08/25 19:23:35 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>

# define OUT_EAT	"is eating"
# define OUT_FORK	"has taken a fork"
# define OUT_SP		"is sleeping"
# define OUT_TK		"is thinking"
# define OUT_DTH	"died"

typedef struct s_data	t_data;

typedef struct s_data_p
{
	t_data			*base_data;
	struct timeval	time_last_meal;
	int				nb_meal;
	size_t			position_p;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}				t_data_p;

typedef struct s_data
{
	struct timeval	time_start;
	size_t			nb_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	m_global;
	bool			philo_is_dead;
	bool			all_philo_are_fulled;
	t_data_p		*table;
}				t_data;

int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_data	*parsing_arg(int argc, char **argv);
int		create_thread(t_data *data);
int		join_thread(t_data *data);
int		create_fork(t_data *data);
long	get_time_in_ms(struct timeval time_start, struct timeval time_now);
void	*choose_routine(void *data);
void	print_output(char *print, t_data_p *data);
int		check_philo_are_fulled(t_data_p *data, size_t i);
int		check_dead_or_full(t_data *data);
void	get_data_for_philo(t_data *base_data, size_t position, t_data_p *data);
#endif
