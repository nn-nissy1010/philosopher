/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:55:45 by nnishiya          #+#    #+#             */
/*   Updated: 2025/10/23 19:16:43 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* 引数: n t_die t_eat t_sleep [must_eat] */
static int parse_args(t_data *d, int argc, char **av)
{
    if (argc != 5 && argc != 6)
    {
        print_error();
        return 1;
    }
    if (atoipos(av[1], &d->n_philo) ||
        atoipos(av[2], &d->time_to_die) ||
        atoipos(av[3], &d->time_to_eat) ||
        atoipos(av[4], &d->time_to_sleep))
    {
        print_error();
        return 1;
    }
    d->must_eat = -1;
    if (argc == 6 && atoipos(av[5], &d->must_eat))
    {
        print_error();
        return 1;
    }
    if (d->n_philo <= 0)
    {
        print_error();
        return 1;
    }
    return 0;
}

static int	init_and_spawn(t_data *d, int argc, char **argv)
{
	memset(d, 0, sizeof(*d));
	if (parse_args(d, argc, argv))
		return (1);
	if (open_semaphores(d))
	{
		close_and_unlink_sems(d);
		return (1);
	}
	if (setup_and_spawn(d))
	{
		close_and_unlink_sems(d);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	d;
	int		died;

	if (init_and_spawn(&d, argc, argv))
		return (1);
	died = monitor_children(&d);
	close_and_unlink_sems(&d);
	free(d.pids);
	return (died ? 1 : 0);
}
