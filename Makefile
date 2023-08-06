# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 15:22:29 by iwillens          #+#    #+#              #
#    Updated: 2023/08/06 15:53:38 by iwillens         ###   ########.fr        #
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

BUILD_TYPE_NAME = square
BUILD_TYPE = ${OBJ_DIR}/.build_square
ifneq (,$(filter rectangle,$(MAKECMDGOALS)))
	BUILD_TYPE_NAME = rectangle
    BUILD_TYPE = ${OBJ_DIR}/.build_rectangle
    CCFLAGS += -DRECTANGLE
endif

BUILD_VERSION_NAME = release
BUILD_VERSION = ${OBJ_DIR}/.build_release
ifneq (,$(filter debug,$(MAKECMDGOALS)))
	BUILD_VERSION_NAME = debug
    BUILD_VERSION = ${OBJ_DIR}/.build_debug
    CCFLAGS += -DDEBUG
endif

all: ${NAME}

square: ${NAME}

debug: ${NAME}

rectangle: ${NAME}

${NAME}: ${OBJS} Makefile ${BUILD_TYPE} ${BUILD_VERSION}
	@gcc ${CCFLAGS} ${OBJS} -o ${NAME}
	@echo "\033[90m${NAME}\033[95m ${BUILD_TYPE_NAME}\033[92m ${BUILD_VERSION_NAME} \033[90mis built. \033[0m"



${OBJ_DIR}/%.o: $(SRC_DIR)/%.c Makefile  ${BUILD_TYPE} ${BUILD_VERSION}
	@mkdir -p ${@D}
	@${CC} ${CCFLAGS} -MMD -c $< -I ${INC_DIR} -o $@


${BUILD_TYPE}:
	@rm -rf ${OBJ_DIR}/.build_square
	@rm -rf ${OBJ_DIR}/.build_rectangle
	@mkdir -p ${OBJ_DIR}
	@touch ${BUILD_TYPE}

${BUILD_VERSION}:
	@rm -rf ${OBJ_DIR}/.build_release
	@rm -rf ${OBJ_DIR}/.build_debug
	@mkdir -p ${OBJ_DIR}
	@touch ${BUILD_VERSION}

clean:
	@rm -rf ${OBJ_DIR}

fclean: clean
	@rm -rf ./${NAME}

re: fclean all	

-include $(DEPENDS)
