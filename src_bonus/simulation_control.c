/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:58:32 by nnishiya          #+#    #+#             */
/*   Updated: 2025/10/23 18:59:06 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int open_semaphores(t_data *d)
{
    sem_unlink(SEM_FORKS_NAME);
    sem_unlink(SEM_PRINT_NAME);

    d->sem_forks = sem_open(SEM_FORKS_NAME, O_CREAT | O_EXCL, 0644, d->n_philo);
    if (d->sem_forks == SEM_FAILED)
    {
        print_error();
        return -1;
    }
    d->sem_print = sem_open(SEM_PRINT_NAME, O_CREAT | O_EXCL, 0644, 1);
    if (d->sem_print == SEM_FAILED)
    {
        print_error();
        return -1;
    }

    return 0;
}

int	setup_and_spawn(t_data *d)
{
	pid_t	pid;
	int		i;

	d->pids = malloc(sizeof(pid_t) * d->n_philo);
	if (!d->pids)
		return (-1);
	memset(d->pids, 0, sizeof(pid_t) * d->n_philo);
	d->start_ms = now_ms();
	i = 0;
	while (i < d->n_philo)
	{
		pid = fork();
		if (pid < 0)
			return (print_error(), -1);
		if (pid == 0)
		{
			philosopher_process(d, i + 1);
			_exit(0);
		}
		d->pids[i] = pid;
		i++;
	}
	return (0);
}

void	cleanup_and_kill_all(t_data *d, int except_idx)
{
	int	i;

	i = 0;
	while (i < d->n_philo)
	{
		if (i != except_idx && d->pids[i] > 0)
			kill(d->pids[i], SIGTERM);
		i++;
	}
}

void close_and_unlink_sems(t_data *d)
{
    if (d->sem_forks && d->sem_forks != SEM_FAILED)
        sem_close(d->sem_forks);
    if (d->sem_print && d->sem_print != SEM_FAILED)
        sem_close(d->sem_print);
    sem_unlink(SEM_FORKS_NAME);
    sem_unlink(SEM_PRINT_NAME);
}
