# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 15:05:17 by mzhitnik          #+#    #+#              #
#    Updated: 2025/01/28 19:36:09 by mzhitnik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_B = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror

INC = -I./inc/

SRCS_PATH = ./src
SRCS_B_PATH = ./src_bonus

OBJS_PATH = ./obj

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

SRCS = $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/utils.c \
		$(SRCS_PATH)/errors.c \
		$(SRCS_PATH)/processing.c \
		$(SRCS_PATH)/quotes.c \
		$(SRCS_PATH)/check.c
SRCS_B = $(SRCS_B_PATH)/main_bonus.c \
		$(SRCS_B_PATH)/utils_bonus.c \
		$(SRCS_B_PATH)/errors_bonus.c \
		$(SRCS_B_PATH)/processing_bonus.c \
		$(SRCS_B_PATH)/quotes_bonus.c \
		$(SRCS_B_PATH)/check_bonus.c

OBJS = $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)
OBJS_B = $(SRCS_B:$(SRCS_B_PATH)/%.c=$(OBJS_PATH)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_PATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

bonus: $(LIBFT) .bonus

.bonus: $(OBJS_B) $(LIBFT)
	$(CC) $(OBJS_B) $(LIBFT) -o $(NAME_B)
	touch .bonus

$(OBJS_PATH)/%.o: $(SRCS_B_PATH)/%.c | $(OBJS_PATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -f .bonus
	@rm -rf $(OBJS_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_B)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

rb: fclean bonus

.PHONY: all clean fclean re
