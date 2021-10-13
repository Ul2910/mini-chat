NAME_S	= server

NAME_C	= client

NAME_B_S	= server_bonus

NAME_B_C	= client_bonus

NAME	= server&client

SRCS_S	= server.c

SRCS_C	= client.c

B_SRCS_S	= server_bonus.c

B_SRCS_C	= client_bonus.c

OBJS_S	= ${SRCS_S:.c=.o}

OBJS_C	= ${SRCS_C:.c=.o}

B_OBJS_S	= ${B_SRCS_S:.c=.o}

B_OBJS_C	= ${B_SRCS_C:.c=.o}

CFLAGS	= -Wall -Wextra -Werror

%.o: %.c
	gcc -c ${CFLAGS} $< -o ${<:.c=.o}

${NAME}: ${NAME_S} ${NAME_C}
	
${NAME_S}: ${OBJS_S}
	gcc ${CFLAGS} ${OBJS_S} -o ${NAME_S}

${NAME_C}: ${OBJS_C}
	gcc ${CFLAGS} ${OBJS_C} -o ${NAME_C}

all:	${NAME_S} ${NAME_C}

${NAME_B_S}: ${B_OBJS_S}
	gcc ${CFLAGS} ${B_OBJS_S} -o ${NAME_B_S}

${NAME_B_C}: ${B_OBJS_C}
	gcc ${CFLAGS} ${B_OBJS_C} -o ${NAME_B_C}

bonus:	${NAME_B_S} ${NAME_B_C}

clean:
	rm -f ${OBJS_S} ${B_OBJS_S} ${OBJS_C} ${B_OBJS_C}

fclean:	clean
	rm -f ${NAME_S} ${NAME_C} ${NAME_B_C} ${NAME_B_S}

re: fclean all

.PHONY:	all fclean clean re bonus




