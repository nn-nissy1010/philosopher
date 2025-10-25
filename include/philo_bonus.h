/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:53:50 by nnishiya          #+#    #+#             */
/*   Updated: 2025/10/23 19:15:30 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <pthread.h>

typedef struct s_data t_data;

typedef struct s_philo {
    int     id;
    long    last_meal;
    int     meals;
    t_data *data;
} t_philo;

typedef struct s_data {
    int     n_philo;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     must_eat;
    long    start_ms;
    sem_t  *sem_forks;
    sem_t  *sem_print;
    pid_t  *pids;
} t_data;

long  now_ms(void);
void  msleep_strict(int ms);
int   atoipos(const char *s, int *out);
long  since_start_ms(t_data *d);
void  safe_print(t_data *d, int id, const char *msg);
void  cleanup_and_kill_all(t_data *d, int except_idx);
void close_and_unlink_sems(t_data *d);
int open_semaphores(t_data *d);
int   setup_and_spawn(t_data *d);
int	monitor_children(t_data *d);



void *watchdog(void *arg);
void  philosopher_process(t_data *d, int id);
void	print_error(void);






# define SEM_FORKS_NAME "/philo_sem_forks"
# define SEM_PRINT_NAME "/philo_sem_print"

#endif
