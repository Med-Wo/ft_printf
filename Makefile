# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mravily <mravily@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/12 13:51:23 by mravily           #+#    #+#              #
#    Updated: 2019/12/22 15:05:47 by mravily          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CC =		gcc

SRC_DIR = 	$(shell find srcs -type d)
INC_DIR = 	$(shell find includes -type d)
OBJ_DIR = 	objs

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

# List de toute les library a linker au projet (le nom - le lib et - le .a)
LIB =

#SRC = $(foreach dir, $(SRC_DIR), $(foreach file, $(wildcard $(dir)/*.c), $(notdir $(file))))
SRC =	$(foreach dir, $(SRC_DIR), $(foreach file, $(wildcard $(dir)/*.c), $(notdir $(file))))
OBJ = 	$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

#Compilation flag
CFLAGS =

#Include flag
IFLAGS = $(foreach dir, $(INC_DIR), -I$(dir))

#Library flag
LFLAGS = $(foreach lib_dir, $(LIB_DIR), -L $(lib_dir)) $(foreach lib, $(LIB), -l $(lib))

# Colors
_GREY=$'\x1b[30m
_RED=$'\x1b[31m
_GREEN=$'\x1b[32m
_YELLOW=$'\x1b[33m
_BLUE=$'\x1b[34m
_PURPLE=$'\x1b[35m
_CYAN=$'\x1b[36m
_WHITE=$'\x1b[37m

all:
				make $(NAME)

show:
				@echo "SRC :\n$(SRC)"
				@echo "OBJ :\n$(OBJ)"
				@echo "CFLAGS :\n$(CFLAGS)"
				@echo "IFLAGS :\n$(IFLAGS)"
				@echo "LFLAGS :\n$(LFLAGS)"

install:
				make -C libs/libft

re-install:
				make -C libs/libft re

$(OBJ_DIR)/%.o : %.c
				@echo "Compiling $(_YELLOW)$@$(_WHITE) ... \c"
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"

$(NAME):		$(OBJ) Makefile
				@echo "-----\n$(_GREEN)Compiling $(_YELLOW)$@ ... \c"
				@ar rc $(NAME) $(OBJ)
				@ranlib $(NAME)
				@echo "$(_RED)DONE\n$(_YELLOW)-----"

exec:			install $(NAME)
				@echo "Compiling the $(_YELLOW)executable$(_WHITE) ... \c"
				@$(CC) srcs/main.c $(NAME) $(CFLAGS) $(IFLAGS) $(LFLAGS) && ./a.out
				@echo "$(_GREEN)DONE$(_WHITE)"

re:				fclean all

clean:
				rm -rf $(OBJ_DIR)

fclean:			clean
				rm -f $(NAME)

.PHONY:			all install re-install exec re clean fclean
