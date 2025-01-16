# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 15:05:17 by mzhitnik          #+#    #+#              #
#    Updated: 2025/01/14 11:55:56 by mzhitnik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc -Wall -Werror -Wextra -I./inc/

SRCS_PATH = ./src
OBJS_PATH = ./obj
LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a
SRCS = $(SRCS_PATH)/main.c $(SRCS_PATH)/parce_args.c $(SRCS_PATH)/args_check.c \
	$(SRCS_PATH)/mapping.c $(SRCS_PATH)/push_swap.c \
	$(SRCS_PATH)/moves_push_swap.c $(SRCS_PATH)/moves_rotate.c \
	$(SRCS_PATH)/chunk_utils.c $(SRCS_PATH)/sort_utils.c $(SRCS_PATH)/costs.c
OBJS = $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_PATH)
	$(CC) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -rf $(OBJS_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
