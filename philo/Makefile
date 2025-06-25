NAME	:=	philo

CC		:= cc

# CFLAGS	:=

SRCS	:=\
		./philo/main.c

OBJS	:= $(SRCS:.c=.o)

$(NAME)	: $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -g

all		: $(NAME)

%.o		: %.c

clean	:
	rm -f $(OBJS)

fclean	: clean
	rm -f $(NAME)

re		: fclean all

.PHONY	: all clean fclean re