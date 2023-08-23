NAME = philo
NAME_BONUS = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3


SRC = philo.c ft_atoi.c philo_action.c philo_manager.c dead_manager.c
SRC_OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) -o $(NAME)

re: fclean all

clean :
	rm -f $(SRC_OBJ)
fclean : clean
	rm -f $(NAME)
