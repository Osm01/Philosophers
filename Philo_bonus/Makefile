NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3


SRC = philo_bonus.c ft_atoi.c philo_action_bonus.c philo_manager_bonus.c
SRC_OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) -o $(NAME)

re: fclean all

clean :
	rm -f $(SRC_OBJ)
fclean : clean
	rm -f $(NAME)
