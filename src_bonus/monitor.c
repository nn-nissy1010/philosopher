/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:55:05 by nnishiya          #+#    #+#             */
/*   Updated: 2025/10/23 19:05:37 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * 子プロセス内で起動される「死の監視」スレッド。
 * last_meal から time_to_die を超えたら "died" を出して exit(1)。
 */
void *watchdog(void *arg)
{
    t_philo *p;
    t_data  *d;
    long now;

    p = (t_philo *)arg;
    d = p->data;
    usleep(2000);

    while (1)
    {
        now = now_ms();
        if (now - p->last_meal > d->time_to_die)
        {
            sem_wait(d->sem_print);
            printf("%ld %d died\n", since_start_ms(d), p->id);
            _exit(1);
        }
        usleep(1000);
    }
    return NULL;
}

int	find_pid_index(t_data *d, pid_t pid)
{
	int	i;

	i = 0;
	while (i < d->n_philo)
	{
		if (d->pids[i] == pid)
			return (i);
		i++;
	}
	return (-1);
}

int	wait_for_child(int *status)
{
	pid_t	pid;

	pid = waitpid(-1, status, 0);
	if (pid <= 0)
		return (-1);
	return (pid);
}

void	handle_child_exit(t_data *d, pid_t pid, int status, int *died)
{
	int	idx;
	int	code;

	idx = find_pid_index(d, pid);
	if (WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
		if (code == 1)
		{
			*died = 1;
			cleanup_and_kill_all(d, idx);
		}
	}
	else if (WIFSIGNALED(status))
	{
		*died = 1;
		cleanup_and_kill_all(d, idx);
	}
}

int	monitor_children(t_data *d)
{
	int	status;
	pid_t	pid;
	int	finished;
	int	died;

	finished = 0;
	died = 0;
	while (finished < d->n_philo)
	{
		pid = wait_for_child(&status);
		if (pid < 0)
			break;
		handle_child_exit(d, pid, status, &died);
		finished++;
	}
	return (died);
}
