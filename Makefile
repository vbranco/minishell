# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/03/07 17:08:49 by vbranco      #+#   ##    ##    #+#        #
#    Updated: 2018/05/19 16:06:08 by vbranco     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME		=	minishell

HEADER		=	mini.h

FILENAMES	=	main.c ft_initialise.c builtins.c builtin_cd.c \
		debug.c

SOURCES		=	$(addprefix ./, $(FILENAMES))

OBJECTS		=	$(addprefix build/, $(FILENAMES:.c=.o))

L_FT		=	./libft

LIB			=	./libft/libft.a

LIB_LNK		=	-L $(L_FT) -l ft

LIB_INC		=	-I $(L_FT)/libft.h

FLAGS		=	-Wall -Wextra -Werror -g

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
