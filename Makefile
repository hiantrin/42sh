# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/19 17:15:33 by szakaria          #+#    #+#              #
#    Updated: 2020/03/01 18:59:43 by hiantrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

CFLAGS = -Wall -Wextra -Werror

_lCYAN = \x1b[96m
_lYELLOW = \x1b[93m
_lGREEN = \x1b[92m
_lBLUE = \x1b[94m
_RED = \x1b[31m
_BOLD = \x1b[1m
_END = \x1b[0m

LIB = libft/libft.a
LIB2 = GTN/get_next_line.c

SRC = mini_cd.c\
		mini_cd2.c\
		mini_echo.c\
		mini_quote.c\
		mini_setenv.c\
		mini_setenv2.c\
		mini_stock.c\
		mini_stock2.c\
		mini_systeme.c\
		mini_unsetenv.c\
		minishell.c\
		minishell1.c\
		minishell2.c\
		myshell.c hazma.c help_to_pipe.c redirect.c help_redirect.c \
		parse_the_re.c trait_the_and.c mini_helpo.c help_trait_and.c \
		help_hamza.c slash_quote.c ft_strsplito.c make_home.c \
		replace_with_env.c get_path.c create_env.c help_all.c mini_type.c \
		and_and.c check_cd_hamza.c one_for_all.c one_for_all_v2.c 42_help.c\
		read_line/affichage_line.c\
		read_line/alt_left_right.c\
		read_line/alt_up_down.c\
		read_line/copy_mode.c\
		read_line/copy_mode2.c\
		read_line/delete_line.c\
		read_line/first_last.c\
		read_line/historique.c\
		read_line/move_left.c\
		read_line/move_right.c\
		read_line/plus_char.c\
		read_line/read_keybord.c\
		read_line/readline.c\
		read_line/readline_v2.c\
		read_line/save_historique.c\

C       = gcc
OBJ = $(SRC:.c=.o)
DEP = sh.h

all : $(NAME)

$(NAME) : LIB $(OBJ) 
		@$(C) $(CFLAGS)  $(OBJ) -o $(NAME) libft/libft.a  -ltermcap

LIB:
		@make -C libft

%.o	: %.c $(DEP)
		$(C) $(CFLAGS)  -o $@ -c $<

clean	:
		@make clean -C libft
		@rm -f $(OBJ)

fclean	: clean
		@make fclean -C libft
		@rm -f $(NAME)

re	: fclean all
