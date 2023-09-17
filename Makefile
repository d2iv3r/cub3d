NAME = game

CC = cc

CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast

L = -L/Users/mel-harc/.brew/Cellar/glfw/3.3.8/lib

I = -I/Users/mel-harc/.brew/Cellar/glfw/3.3.8/include/GLFW

SUB = -framework Cocoa -framework OpenGL -framework IOKit -lglfw 

mlx = /Users/mel-harc/MLX42/build/libmlx42.a

SEGS = -Wuninitialized -fsanitize=address,undefined,integer -g

LIBFT = libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_split.c libft/ft_substr.c libft/ft_isalpha.c\
		libft/ft_strdup.c libft/ft_strlen.c libft/ft_memcpy.c libft/ft_memset.c libft/ft_isdigit.c\
		libft/ft_atoi.c libft/ft_strcmp.c libft/ft_strchr.c libft/ft_strnstr.c libft/ft_isempty.c\
		libft/ft_strlcpy.c libft/get_long_line.c


UTILS = parsing/utils_map.c parsing/utils_map2.c parsing/mr_cleaner.c parsing/utils_map3.c \
		main_function/draw_map.c main_function/hook_functions.c main_function/utils.c \
		main_function/raycasting.c main_function/utils_raycasting.c main_function/init.c\

SRC = $(LIBFT) $(UTILS) cub3d.c parsing/check_map.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) cub3d.h
	$(CC) $(CFLAGS) $(OBJ) $(SUB) $(LIBS) $(SEGS) -o $(NAME) $(L) $(I) $(mlx)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(SEGS)  -c $< -o $@ $(I)


clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean all fclean re
