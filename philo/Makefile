NAME	:=	philo

CC		:= cc

# CFLAGS	:=

SRCS	:=\
		./main.c

OBJS	:= $(SRCS:.c=.o)

$(NAME)	: $(OBJS)
	$(CC) $(SRCS) -o $(NAME) -g

all		: $(NAME)

%.o		: %.c
	$(CC) -c $< -o $@

clean	:
	rm -f $(OBJS)

fclean	: clean
	rm -f $(NAME)

re		: fclean all

.PHONY	: all clean fclean re