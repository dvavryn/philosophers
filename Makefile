# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 23:52:03 by dvavryn           #+#    #+#              #
#    Updated: 2025/08/05 01:17:55 by dvavryn          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



RED    = \033[0;31m
GREEN  = \033[0;32m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
RESET  = \033[0m

NAME    := philo
SRCDIR  := src
OBJDIR  := obj
INCDIR  := inc

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I$(INCDIR) -pthread -g

SRCS    := \
			$(SRCDIR)/check.c \
			$(SRCDIR)/clean.c \
			$(SRCDIR)/init.c \
			$(SRCDIR)/join_threads.c \
			$(SRCDIR)/main.c \
			$(SRCDIR)/routine_monitor.c \
			$(SRCDIR)/routine_philo.c \
			$(SRCDIR)/start_simulation.c \
			$(SRCDIR)/utils.c			
			
OBJS    := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n$(GREEN)🚀 Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✔ Successfully built $(NAME)!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(BLUE)📁 Created $(OBJDIR) directory$(RESET)"

clean:
	@if [ -d "$(OBJDIR)" ]; then \
		rm -rf $(OBJDIR); \
		echo "$(RED)🧹 Removed $(OBJDIR) directory$(RESET)"; \
	else \
		echo "$(YELLOW)⚠️ No object files to clean$(RESET)"; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "$(RED)🧹 Removed $(NAME)$(RESET)"; \
	else \
		echo "$(YELLOW)⚠️ $(NAME) not found$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean re