GREEN   = \033[1;32m
WHITE   = \033[0;m

SRC = 	ft_philosophers_bonus.c \
		ft_philosophers_utils_bonus.c \
		ft_philosophers_utils2_bonus.c \
		

OBJ= $(SRC:.c=.o)

CC = gcc -Wall -Wextra -Werror


NAME = philosophersbonus

bonus:			$(NAME)

philosophersbonus :		$(OBJ)
				@$(CC)  ${OBJ} -o $(NAME) -lpthread 
				@printf "\n[$(GREEN)generated$(WHITE)] philosophers 😴 \n"

obj/%.o:src/%.c
				@mkdir -p  obj
				@$(CC) -o   $@ -c $< -lpthread  $(CFLAGS)
			

clean:
				@rm -f $(OBJ) core
				@printf "\n[$(GREEN)cleaned$(WHITE)] .o  \n"

fclean:			clean
				@rm -f $(NAME)
				@printf "\n[$(GREEN)cleaned$(WHITE)] $(NAME)  \n"

re:				fclean bonus

.PHONY:			all clean fclean re