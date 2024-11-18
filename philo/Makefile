NAME = philo 

SRC_FILES =  main.c tools1.c tools2.c g_collector.c simulation.c 

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror 

philo/%.o : philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

clean :
	rm -f $(OBJ_FILES)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean 