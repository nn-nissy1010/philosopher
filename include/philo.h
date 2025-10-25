#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long            last_meal;
    int             meals;
    struct s_data   *data;
}   t_philo;

typedef struct s_data
{
    int             n_philo;
    pthread_mutex_t *forks;
    t_philo         *philos;
    pthread_mutex_t print_mutex;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;
    int             someone_dead;
}   t_data;


// utils.c
long    get_time_ms(void);
void    msleep(int ms);

void    *routine(void *arg);
void *monitor(void *arg);
void print_action(t_philo *p, const char *msg);
void	print_error(void);
int	ft_atoi(const char *str);

#endif
