/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:55:23 by nnishiya          #+#    #+#             */
/*   Updated: 2025/10/23 18:56:33 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philo	*init_philosopher(t_data *d, int id)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (!p)
		_exit(1);
	p->id = id;
	p->data = d;
	p->meals = 0;
	p->last_meal = d->start_ms;
	return (p);
}

static void	start_watchdog_thread(t_philo *p)
{
	pthread_t	th;

	pthread_create(&th, NULL, watchdog, p);
	pthread_detach(th);
	if (p->id % 2 == 0)
		usleep(1000);
}

static void	run_philosopher_loop(t_data *d, t_philo *p)
{
	while (1)
	{
		sem_wait(d->sem_forks);
		safe_print(d, p->id, "has taken a fork");
		sem_wait(d->sem_forks);
		safe_print(d, p->id, "has taken a fork");

		p->last_meal = now_ms();
		safe_print(d, p->id, "is eating");
		msleep_strict(d->time_to_eat);
		p->meals++;

		sem_post(d->sem_forks);
		sem_post(d->sem_forks);

		if (d->must_eat > 0 && p->meals >= d->must_eat)
			_exit(0);

		safe_print(d, p->id, "is sleeping");
		msleep_strict(d->time_to_sleep);
		safe_print(d, p->id, "is thinking");
	}
}

void	philosopher_process(t_data *d, int id)
{
	t_philo	*p;

	p = init_philosopher(d, id);
	start_watchdog_thread(p);
	run_philosopher_loop(d, p);
}
