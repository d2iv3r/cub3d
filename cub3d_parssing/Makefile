NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror
#-fsanitize=address

LIBFT = libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_split.c libft/ft_substr.c libft/ft_isalpha.c\
		libft/ft_strdup.c libft/ft_strlen.c libft/ft_memcpy.c libft/ft_memset.c libft/ft_isdigit.c\
		libft/ft_atoi.c libft/ft_strcmp.c libft/ft_strchr.c libft/ft_strnstr.c libft/ft_isempty.c\
		libft/ft_strlcpy.c libft/get_long_line.c


UTILS = utils_map.c utils_map2.c mr_cleaner.c utils_map3.c

SRC = $(LIBFT) $(UTILS) cub3d.c check_map.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

# $(NAME): $(OBJ) cub3d.h
# 	$(CC) $(CFLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

# $(NAME): $(OBJ) cub3d.h
# 	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME) : $(OBJ) cub3d.h
	$(CC) $(CFLAGS) $(OBJ) -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGl -framework Appkit -o $@

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

# %.o : %.c
# 	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean all fclean re
