# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/16 15:10:33 by spoliart          #+#    #+#              #
#    Updated: 2021/09/06 04:05:16 by spoliart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_END		=	\e[0m

_RED		=	\e[31m
_GREEN		=	\e[32m
_YELLOW		=	\e[33m

NAME =	pipex

SRCS =	pipex.c \
		pipex_utils.c \
		error.c

DIR_SRCS = ./srcs/
DIR_OBJS = ./objs/
OBJS = $(SRCS:%.c=$(DIR_OBJS)%.o)

FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
INC = -I includes/

all: $(NAME)

$(NAME): $(OBJS)
	@printf "\033[2K\r$(_GREEN) All pipex files compiled into '$(DIR_OBJS)'. $(_END)✅\n"
	@make -C libft
	@gcc $(FLAGS) $(OBJS) $(INC) $(LIBFT) -o $(NAME)
	@printf "$(_GREEN) Binary '$(NAME)' created. $(_END)✅\n"

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
	@printf "$(_YELLOW)Compiling $< $(_END)⌛"
	@gcc $(FLAGS) $(INC) -c $< -o $@

$(OBJS): | $(DIR_OBJS)

$(DIR_OBJS):
	@mkdir -p $(DIR_OBJS)

clean:
	@make clean -C libft
	@rm -rf $(DIR_OBJS)
	@printf "$(_RED) '$(DIR_OBJS)' has been deleted. $(_END)🗑️\n"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME) $(CHECKER)
	@printf "$(_RED) '$(NAME)' has been deleted. $(_END)🗑️\n"

re:
	@make fclean
	@make

.PHONY:	all $(NAME) clean fclean re
