# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obajali <obajali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 21:04:15 by obajali           #+#    #+#              #
#    Updated: 2025/01/18 19:08:22 by obajali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = pipex
AR = ar -rcs
CC = cc
CFLAG = -Wall -Wextra -Werror
RM = rm -fr


SRC = pipex.c ft_splite.c pipex_utils1.c pipex_utils2.c pipex_utils3.c 
BNS = pipex_bonus.c ft_splite.c get_next_line.c error.c pipex_utils1.c pipex_utils2.c pipex_utils3.c

OBJS = $(SRC:.c=.o)
OBJB = $(BNS:.c=.o)
BONUS_RE = .bonus

all : ${NAME}

${NAME} : ${OBJS}
	${CC} ${OBJS} -o ${NAME}
	
%.o : %.c 
	${CC} ${CFLAG} -c $< -o $@

clean :
	${RM} ${OBJB} ${OBJS}
	@$(RM) $(BONUS_RE)
	
fclean : clean
	${RM} ${NAME}
	
bonus : $(BONUS_RE)

$(BONUS_RE) : $(NAME) $(OBJB)
	${CC} ${OBJB} -o ${NAME}
	@touch $(BONUS_RE)

re : fclean all
  
.PHONY : re clean fclean