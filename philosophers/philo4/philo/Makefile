# 🏛️ Philosophers Makefile
# Author: Dominic Vavryn
# Date:   2025/07/29

# ===== Colors =====
RED    = \033[0;31m
GREEN  = \033[0;32m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
RESET  = \033[0m

# ===== Project Configuration =====
NAME    := philo
SRCDIR  := src
OBJDIR  := obj
INCDIR  := include

# ===== Compiler and Flags =====
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I$(INCDIR) -pthread  # Added -pthread for philosophers
LDFLAGS := 
LIBS    := 

# ===== Source Files =====
SRCS    := \
            $(SRCDIR)/init.c \
            $(SRCDIR)/main.c \
            $(SRCDIR)/monitor.c \
            $(SRCDIR)/routine.c \
            $(SRCDIR)/utils.c   # Fixed typo (OBBS → OBJS)

OBJS    := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# ===== Progress Bar =====
TOTAL   := $(words $(SRCS))
COUNT   := 0
PERCENT := 0

define progress_bar
	@$(eval COUNT=$(shell expr $(COUNT) + 1))
	@$(eval PERCENT=$(shell expr $(COUNT) \* 100 / $(TOTAL)))
	@printf "[$(GREEN)%*s$(RESET)%*s] $(YELLOW)%3d%%$(RESET) $(BLUE)Building$(RESET) %s\r" \
		"$(shell expr $(PERCENT) / 2)" "" \
		"$(shell expr 50 - $(PERCENT) / 2)" "" \
		"$(PERCENT)" "$(notdir $<)"
endef

# ===== Main Targets =====
all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n$(GREEN)🚀 Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✔ Successfully built $(NAME)!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(call progress_bar)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(BLUE)📁 Created $(OBJDIR) directory$(RESET)"

# ===== Cleaning =====
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

# ===== Extras =====
.PHONY: all clean fclean re

# Run the program
run: all
	@echo "$(BLUE)🏃 Running $(NAME)...$(RESET)"
	@./$(NAME)

# Debug build (with -g flag)
debug: CFLAGS += -g
debug: re

# Check code style (norminette)
norm:
	@echo "$(BLUE)🔍 Checking code style...$(RESET)"
	@norminette $(SRCDIR) $(INCDIR) | grep -v "OK!" || true
	@echo "$(GREEN)✔ Norminette check complete!$(RESET)"