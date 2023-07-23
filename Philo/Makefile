NAME = philo
CC = cc
CFLAGS = #-fsanitize=thread -g3#-Wall -Wextra -Werror


SRC = philo.c ft_atoi.c
SRC_OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) -o $(NAME)

re: fclean all

clean :
	rm -f $(SRC_OBJ)
fclean : clean
	rm -f $(NAME)
