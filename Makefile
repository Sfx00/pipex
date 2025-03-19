NAME= pipex
CC= cc
CFLAG= -Wall -Wextra -Werror
RM= rm -fr

SRC= pipex.c pipex_memory.c pipex_path.c pipex_string.c pipex_utils.c ft_splite.c

OBJS= $(SRC:%.c=%.o)

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME}
	
%.o: %.c 
	${CC} ${CFLAG} -c $< -o $@

clean:
	${RM} ${OBJS}
	
fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re