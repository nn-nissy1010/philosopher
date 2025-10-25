/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:54:44 by nnishiya          #+#    #+#             */
/*   Updated: 2025/10/23 18:46:02 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long now_ms(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void msleep_strict(int ms)
{
    long start;
    
    start = now_ms();
    while (now_ms() - start < ms)
        usleep(200);
}

long since_start_ms(t_data *d)
{
    return (now_ms() - d->start_ms);
}

int atoipos(const char *s, int *out)
{
    long v;
    
    v = 0;
    if (!s || !*s)
        return -1;
    for (int i = 0; s[i]; ++i)
    {
        if (s[i] < '0' || s[i] > '9')
            return -1;
        v = v * 10 + (s[i] - '0');
        if (v > 1000000000)
            return -1;
    }
    if (v <= 0)
        return -1;
    *out = (int)v;
    return 0;
}

void safe_print(t_data *d, int id, const char *msg)
{
    sem_wait(d->sem_print);
    printf("%ld %d %s\n", since_start_ms(d), id, msg);
    sem_post(d->sem_print);
}

void	print_error(void)
{
	write(2, "Error\n", 6);
}
