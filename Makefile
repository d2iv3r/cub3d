NAME = cub3D

NAME_B = cub3D_B

CC = cc

CFLAGS = -Wall -Wextra -Werror -Wunreachable-code

L = -L/Users/mel-harc/.brew/Cellar/glfw/3.3.8/lib

I = -I/Users/mel-harc/.brew/Cellar/glfw/3.3.8/include/GLFW

SUB = -framework Cocoa -framework OpenGL -framework IOKit -lglfw

mlx = $(PWD)/MLX42/build/libmlx42.a

LIBFT = mandatory/libft/ft_strrchr.c mandatory/libft/ft_strncmp.c mandatory/libft/ft_split.c mandatory/libft/ft_substr.c mandatory/libft/ft_isalpha.c\
		mandatory/libft/ft_strdup.c mandatory/libft/ft_strlen.c mandatory/libft/ft_memcpy.c mandatory/libft/ft_memset.c mandatory/libft/ft_isdigit.c\
		mandatory/libft/ft_atoi.c mandatory/libft/ft_strcmp.c mandatory/libft/ft_strchr.c mandatory/libft/ft_strnstr.c mandatory/libft/ft_isempty.c\
		mandatory/libft/ft_strlcpy.c mandatory/libft/get_long_line.c

PARS = mandatory/parsing/check_map.c mandatory/parsing/get_elements.c mandatory/parsing/check_elements.c\
		mandatory/parsing/utils_map.c mandatory/parsing/utils.c mandatory/parsing/mr_cleaner.c


UTILS = mandatory/main_function/draw_map.c mandatory/main_function/hook_functions.c mandatory/main_function/utils.c \
			mandatory/main_function/raycasting.c mandatory/main_function/utils_raycasting.c mandatory/main_function/init.c\

LIBFT_B = bonus/libft/ft_strrchr.c bonus/libft/ft_strncmp.c bonus/libft/ft_split.c bonus/libft/ft_substr.c bonus/libft/ft_isalpha.c\
		bonus/libft/ft_strdup.c bonus/libft/ft_strlen.c bonus/libft/ft_memcpy.c bonus/libft/ft_memset.c bonus/libft/ft_isdigit.c\
		bonus/libft/ft_atoi.c bonus/libft/ft_strcmp.c bonus/libft/ft_strchr.c bonus/libft/ft_strnstr.c bonus/libft/ft_isempty.c\
		bonus/libft/ft_strlcpy.c bonus/libft/get_long_line.c \

PARS_B = bonus/parsing/check_map_bonus.c bonus/parsing/get_elements_bonus.c bonus/parsing/check_elements_bonus.c\
		bonus/parsing/utils_map_bonus.c bonus/parsing/utils_bonus.c bonus/parsing/mr_cleaner_bonus.c

UTILS_B = bonus/main_function/draw_map_bonus.c bonus/main_function/hook_functions_bonus.c bonus/main_function/utils_bonus.c \
		bonus/main_function/raycasting_bonus.c bonus/main_function/utils_raycasting_bonus.c bonus/main_function/init_bonus.c\

SRC = $(LIBFT) $(UTILS) $(PARS) mandatory/cub3d.c mandatory/textures.c

SRC_B = $(LIBFT_B) $(UTILS_B) $(PARS_B) bonus/cub3d_bonus.c bonus/textures_bonus.c

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) mandatory/cub3d.h  
	$(CC) $(CFLAGS) $(OBJ) $(SUB) $(SEGS) -o $(NAME) $(L) $(I) $(mlx)

%.o: %.c mandatory/cub3d.h mandatory/libft/libft.h
	$(CC) $(CFLAGS) $(SEGS)  -c $< -o $@ $(I)

bonus : $(OBJ_B) bonus/cub3d_bonus.h bonus/libft/libft.h
		$(CC) $(CFLAGS) $(SUB) $(OBJ_B)  -o $(NAME_B) $(L) $(I) $(mlx)

clean :
	rm -rf $(OBJ) $(OBJ_B)

fclean : clean
	rm -rf $(NAME) $(NAME_B)

re : fclean all bonus

.PHONY : clean all fclean re