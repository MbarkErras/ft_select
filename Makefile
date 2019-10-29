NAME=ft_select

SRCS=	ft_select.c \
		ft_select_listener.c \
		ft_select_utilities.c \
		rendering.c \
		checkers.c \
		terminal.c \
		error_handling.c \

OBJS=$(SRCS:.c=.o)

LIBS_DIR=libs
OBJS_DIR=build
SRCS_DIR=srcs
OBJS_PATH=$(addprefix $(OBJS_DIR)/, $(OBJS))
SRCS_PATH=$(addprefix $(SRCS_DIR)/, $(SRCS))
INCLUDES=includes

FLAGS= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS_PATH) $(INCLUDES)/ft_select.h
	make -C $(LIBS_DIR)/centropy
	gcc $(OBJS_PATH) -I$(INCLUDES) -I$(LIBS_DIR)/centropy/includes -I$(LIBS_DIR)/simplist/includes $(LIBS_DIR)/*/*.a -o $(NAME) -ltermcap

$(OBJS_PATH): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	gcc $(FLAGS) -I$(INCLUDES) -I$(LIBS_DIR)/centropy/includes -I$(LIBS_DIR)/simplist/includes -c $< -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

clean:
	make -C $(LIBS_DIR)/centropy clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBS_DIR)/centropy fclean
	rm -rf $(NAME)

re: fclean all
