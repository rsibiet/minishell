# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/22 17:59:05 by rsibiet           #+#    #+#              #
#    Updated: 2016/02/16 10:33:26 by rsibiet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FTC = recov_env_minishell.c \
	  recov_env_minishell_2.c \
	  find_command_minishell.c \
	  find_command_minishell_2.c \
	  env_minishell.c \
	  env_minishell_2.c \
	  env_minishell_3.c \
	  define_av.c \
	  define_av_2.c \
	  define_av_3.c \
	  define_av_4.c \
	  update_env.c \
	  update_env_2.c \
	  update_env_3.c \
	  opt_cd.c \
	  error_minishell.c \
	  error_minishell_2.c \
	  error_minishell_3.c \
	  finish_to_norme_sh.c \
	  finish_to_norme_2.c \
	  split_simple_quote.c

FTO = $(subst .c,.o,$(FTC))

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(FTO)
	@echo ""
	@make -C ./libft
	@gcc -o $(NAME) $(FTO) ./libft/libft.a
	@echo "\033[32m$(NAME) created!\033[0m"

%.o: %.c
	@gcc -Wall -Wextra -Werror -I./libft/ -c $<
	@echo "\033[34m#\033[0m\c"

clean:
	@make -C ./libft clean
	@rm -rf $(FTO)
	@echo "\033[33m$(NAME) object deleted!\033[0m"

fclean: clean
	@make -C ./libft fcleana
	@rm -rf $(NAME)
	@echo "\033[31m$(NAME) deleted!\033[0m"

re: fclean all
