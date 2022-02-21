GREEN   = \033[1;32m
WHITE   = \033[0;m

SRC = 	ft_philosophers.c \
		ft_philosophers_utils.c \
		ft_philosophers_utils2.c \
		

OBJ= $(SRC:.c=.o)
OBJ	:= $(addprefix obj/,${OBJ})

CC = gcc

CFLAGS =   -I includes

NAME = philosophers

all:			$(NAME)

philosophers :		$(OBJ)
				@$(CC) ${CFLAGS} ${OBJ} -o $(NAME) -lpthread 
				@printf "\n[$(GREEN)generated$(WHITE)] philosophers 😴 \n"

obj/%.o:src/%.c
				@mkdir -p  obj
				@$(CC) -o   $@ -c $< -lpthread  $(CFLAGS)
			

clean:
				@rm -f $(OBJ) core
				@printf "\n[$(GREEN)cleaned$(WHITE)] .o  \n"

fclean:			clean
				@printf "\n[$(GREEN)cleaned$(WHITE)] $(NAME)  \n"

re:				fclean all

.PHONY:			all clean fclean re