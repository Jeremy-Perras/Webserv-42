NAME = webserv

SRCS = main.cpp Socket.cpp Listen.cpp Bind.cpp Message.cpp

INCLUDES = -I.

OBJS = $(SRCS:.cpp=.o)

CC = g++

FLAGS = -Wall -g -Wextra -Werror #-std=c++98

.c.o:
		${CC} ${FLAGS} -I. -c $< -o ${<:.cpp=.o}

$(NAME) : $(OBJS)

	$(CC) $(FLAGS) -o $(NAME) $(INCLUDES) $(OBJS)

all : $(NAME)


test :
	$(CC) -g $(FLAGS) -o $(NAME) $(SRCS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
