NAME = fdf
CC = gcc
CFLAGS = -Wall -Werror -Wextra
MLX_PATH = ./mlx
LIBFT_PATH = ./libft
LIBFT_URL = https://github.com/Magazem/libft.git
INCLUDES = -I$(MLX_PATH) -I$(LIBFT_PATH)

SRCS = ./srcs/fdf.c \
       ./srcs/window_manager.c \
       ./srcs/parse.c \
       ./srcs/utils.c \
       ./srcs/get_next_line.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(LIBFTDIR)
	@$(MAKE) --no-print-directory bonus -C $(LIBFTDIR)

$(LIBFTDIR):
	@echo "$(CYAN)Downloading libft...$(NORMAL)"
	git clone -q $(LIBFT_URL) $(LIBFTDIR)
	@echo "$(GREEN)Libft downloaded successfully$(NORMAL)"

$(NAME): mlx $(OBJS) 
	make -C $(LIBFT_PATH)
	make -C $(MLX_PATH)
	$(CC) $(LDFLAGS) $(OBJS) $(INCLUDES) -L$(MLX_PATH) -L$(LIBFT_PATH) \
		-o $(NAME) $(LIBFT_PATH)/libft.a $(MLX_PATH)/libmlx.a \
		-lXext -lX11 -lm -lbsd -lz

mlx: 
	wget https://cdn.intra.42.fr/document/document/26480/minilibx-linux.tgz
	tar -xvzf minilibx-linux.tgz
	rm -f minilibx-linux.tgz
	mv minilibx-linux mlx

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_PATH)
	make clean -C $(MLX_PATH)

fclean: clean
	rm -f $(NAME)
	rm -rf ${LIBFT_PATH}
	rm -rf ./mlx

re: fclean all

.PHONY: all clean fclean re
