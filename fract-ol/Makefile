NAME	= fractol

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -Imlx

MLX_PATH	= libs/minilibx_opengl_20191021
MLX			= $(MLX_PATH)/libmlx.a

FT_PRINF_PATH	= libs/ft_printf
FT_PRINTF		= $(FT_PRINF_PATH)/libftprintf.a

SRCS	= src/fractal_types.c \
		  src/fractol.c \
		  src/img_num.c \
		  src/mouse_key.c \

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

makemlx:
	@make -C $(MLX_PATH)

makeftprintf:
	@make -C $(FT_PRINF_PATH)

$(NAME): makemlx makeftprintf $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(MLX) $(FT_PRINTF) -lmlx -framework OpenGL -framework AppKit -L $(MLX_PATH) 

clean:
	@rm -f $(OBJS)
	@make -C $(MLX_PATH) clean
	@make -C $(FT_PRINF_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(MLX_PATH) clean
	@make -C $(FT_PRINF_PATH) fclean

re: fclean all