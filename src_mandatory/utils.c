/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:14:35 by nnishiya          #+#    #+#             */
/*   Updated: 2025/10/23 15:39:33 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time_ms(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void msleep(int ms)
{
    long start;
    long now;

    start = get_time_ms();
    while (1)
    {
        now = get_time_ms();
        if (now - start >= ms)
            break;
        usleep(100);
    }
}

void print_action(t_philo *p, const char *msg)
{
    pthread_mutex_lock(&p->data->print_mutex);
    if (!p->data->someone_dead)
        printf("%ld %d %s\n", get_time_ms(), p->id, msg);
    pthread_mutex_unlock(&p->data->print_mutex);
}

void	print_error(void)
{
	write(2, "Error\n", 6);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}
