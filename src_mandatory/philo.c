/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:15:23 by nnishiya          #+#    #+#             */
/*   Updated: 2025/10/23 18:50:35 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int parse_args(t_data *data, int argc, char **argv)
{
    if (argc < 5 || argc > 6)
    {
        print_error();
        return (1);
    }
    data->n_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->must_eat = ft_atoi(argv[5]);
    else
        data->must_eat = -1;
    data->someone_dead = 0;
    return (0);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	if (parse_args(data, argc, argv))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->forks || !data->philos)
		return (1);
	i = 0;
    while (i < data->n_philo)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
	pthread_mutex_init(&data->print_mutex, NULL);
	return (0);
}

static void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->n_philo];
		data->philos[i].last_meal = get_time_ms();
		data->philos[i].meals = 0;
		data->philos[i].data = data;
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		i++;
	}
}

static void	cleanup_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;
	int			i;

	if (init_data(&data, argc, argv))
		return (1);
	create_threads(&data);
	pthread_create(&monitor_thread, NULL, monitor, &data);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data.n_philo)
		pthread_join(data.philos[i++].thread, NULL);
	cleanup_data(&data);
	return (0);
}
