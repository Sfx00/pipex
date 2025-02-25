# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obajali <obajali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 21:04:15 by obajali           #+#    #+#              #
#    Updated: 2025/02/25 17:23:06 by obajali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = pipex
AR = ar -rcs
CC = cc
CFLAG = -Wall -Wextra -Werror -g3
RM = rm -fr


SRC = mandatory/pipex.c mandatory/ft_splite.c mandatory/pipex_utils1.c mandatory/pipex_utils2.c mandatory/pipex_utils3.c 
BNS = bonus/pipex_bonus.c bonus/ft_splite.c bonus/get_next_line.c bonus/error.c bonus/pipex_utils1_bonus.c bonus/pipex_utils2_bonus.c bonus/pipex_utils3_bonus.c

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