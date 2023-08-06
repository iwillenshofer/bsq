# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 15:22:29 by iwillens          #+#    #+#              #
#    Updated: 2023/08/06 02:24:43 by iwillens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

CC = gcc
CCFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

SRC_DIR = ./srcs
OBJ_DIR = ./build
INC_DIR = ./includes

SRCS = ${SRC_DIR}/gnl.c \
 		${SRC_DIR}/libft.c \
 		${SRC_DIR}/validate.c \
 		${SRC_DIR}/print.c \
 		${SRC_DIR}/parse.c \
		${SRC_DIR}/solve.c \
		${SRC_DIR}/debug.c \
 		${SRC_DIR}/main.c

OBJS = $(patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRCS})

DEPENDS = $(patsubst ${OBJ_DIR}/%.o, ${OBJ_DIR}/%.d, ${OBJS})

all: ${NAME}

${NAME}: ${OBJS} Makefile
	@gcc ${CCFLAGS} ${OBJS} -o ${NAME}
	@echo "\033[96m${NAME} is built. \033[0m"

${OBJ_DIR}/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p ${@D}
	@${CC} ${CCFLAGS} -MMD -c $< -I ${INC_DIR} -o $@

clean:
	@rm -rf ${OBJ_DIR}

fclean: clean
	@rm -rf ./${NAME}

re: fclean all	

-include $(DEPENDS)
