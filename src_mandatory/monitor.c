/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:28:22 by nnishiya          #+#    #+#             */
/*   Updated: 2025/10/30 11:44:28 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher_death(t_data *data)
{
	int		i;
	long	now;

	i = 0;
	while (i < data->n_philo)
	{
		now = get_time_ms();
		if (now - data->philos[i].last_meal > data->time_to_die + 3)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %d died\n", now, data->philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			data->someone_dead = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_all_meals_done(t_data *data)
{
	int	i;
	int	done;

	if (data->must_eat <= 0)
		return (0);
	i = 0;
	done = 1;
	while (i < data->n_philo)
	{
		if (data->philos[i].meals < data->must_eat)
			done = 0;
		i++;
	}
	if (done)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("all philosophers have eaten %d times\n", data->must_eat);
		pthread_mutex_unlock(&data->print_mutex);
		data->someone_dead = 1;
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!data->someone_dead)
	{
		if (check_philosopher_death(data))
			return (NULL);
		if (check_all_meals_done(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
