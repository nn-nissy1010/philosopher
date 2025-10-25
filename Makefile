# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 22:20:03 by nnishiya          #+#    #+#              #
#    Updated: 2025/10/23 19:12:31 by nnishiya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME        = philo
NAME_BONUS  = philo_bonus

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -pthread -Iinclude
RM      = rm -f

# mandatory
SRC_DIR     = src_mandatory
SRC         = $(SRC_DIR)/philo.c \
              $(SRC_DIR)/routine.c \
              $(SRC_DIR)/monitor.c \
              $(SRC_DIR)/utils.c
OBJ         = $(SRC:.c=.o)

# bonus
SRC_BONUS_DIR = src_bonus
SRC_BONUS     = $(SRC_BONUS_DIR)/philo.c \
                $(SRC_BONUS_DIR)/routine.c \
                $(SRC_BONUS_DIR)/monitor.c \
				$(SRC_BONUS_DIR)/routine.c \
				$(SRC_BONUS_DIR)/simulation_control.c \
                $(SRC_BONUS_DIR)/utils.c
OBJ_BONUS     = $(SRC_BONUS:.c=.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c include/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c include/philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
