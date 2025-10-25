/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:14:55 by nnishiya          #+#    #+#             */
/*   Updated: 2025/10/23 18:51:36 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->left_fork);
	}
	else
	{
		pthread_mutex_lock(p->left_fork);
		pthread_mutex_lock(p->right_fork);
	}
	print_action(p, "has taken forks");
}

static void	eat(t_philo *p)
{
	print_action(p, "is eating");
	p->last_meal = get_time_ms();
	p->meals++;
	msleep(200);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

static void	sleep_and_think(t_philo *p)
{
	print_action(p, "is sleeping");
	msleep(200);
	print_action(p, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!p->data->someone_dead)
	{
		take_forks(p);
		eat(p);
		sleep_and_think(p);
	}
	return (NULL);
}
