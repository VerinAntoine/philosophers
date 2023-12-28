NAME	:= philo
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror

OBJ_DIR	:= ./obj

define SRC :=
	main.c
endef
SRC := $(strip $(SRC))

OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))

$(NAME): $(OBJS)
	@echo '* Assembling $(NAME)'
	@$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@echo '- Compiling $<'
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	@echo '! Removing objs'
	@rm -rf $(OBJS) $(OBJS_BONUS)

.PHONY: fclean
fclean: clean
	@echo '! Removing $(NAME)'
	@rm -rf $(NAME)

.PHONY: re
re: fclean $(NAME)

.PHONY: norm
norm:
	@make -C $(LIBFT_DIR) norm $(MAKE_FLAG)
	@norminette $(SRC_DIR) $(INCLD_DIR)
