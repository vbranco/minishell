# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/03/07 17:08:49 by vbranco      #+#   ##    ##    #+#        #
#    Updated: 2018/06/27 18:56:21 by vbranco     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME		=	minishell

HEADER		=	mini.h

FILENAMES	=	main.c tools_lst_env.c builtins.c builtin_cd.c builtin_cd2.c builtin_env.c builtin_setenv.c builtin_unsetenv.c parsing.c\
	exe.c tools.c tools_env.c tools_lst_parse.c head_prompt.c tools_mini.c \
	tools_cd.c tools_exe.c tools_parsing.c

SOURCES		=	$(addprefix ./, $(FILENAMES))

OBJECTS		=	$(addprefix build/, $(FILENAMES:.c=.o))

L_FT		=	./libft

LIB			=	./libft/libft.a

LIB_LNK		=	-L $(L_FT) -l ft

LIB_INC		=	-I $(L_FT)/libft.h

LAGS		=	-Wall -Wextra -Werror -g #penser a enlever le -g

.PHONY: all clean fclean re

all: $(NAME)

clean:
		@echo "\033[31m Cleanning minishell"
		@rm -rf build/
#		@$(MAKE) -C $(L_FT) clean

fclean: clean
	    @echo "\033[31m FCleanninf minishell"
		@rm -f $(NAME)
#		@$(MAKE) -C $(L_FT) fclean

re:		fclean all#enlever
		@echo "\033[32m RE minishell"
#		@$(MAKE) fclean
#		@$(MAKE) all

build:
	    @echo "\033[32m Making minishell"
		@mkdir build/

$(NAME): $(OBJECTS)
#		@$(MAKE) -C $(L_FT)
		@gcc $(FLAGS) -I  $(HEADER) $(SOURCES) $(LIB) -o $@ #-g
		@echo " Ready to play"

build/%.o: ./%.c | build
	    @gcc $(FLAGS) $(LIB_INC) -I $(HEADER) -c $< -o $@
