# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rkaras <rkaras@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2024/10/10 16:44:13 by rkaras        #+#    #+#                  #
#    Updated: 2024/10/25 16:30:24 by rkaras        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SOURCE = main.c \
		utils.c \
		input_checker.c \
		inits.c \
		routine.c \
		threads.c \
		routine_actions.c \
		end_checks.c \
		cleaner.c \

OBJECTS = $(SOURCE:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
		$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) $(OBJECTS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re