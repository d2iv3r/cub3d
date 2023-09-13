/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:23:34 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/11 17:30:30 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "mlx.h"

typedef struct s_element
{
	char	*id;
	char	*info;
	int		color[3];
}			t_element;

typedef struct s_map
{
	char		*file;
	int			fd;
	t_element	*elem;
	char		**map;
	int			x;
	int			y;
}			t_map;

//	LIBFT
// char		*ft_strrchr(const char *s, int c);
// int			ft_strncmp(const char *s1, const char *s2, size_t n);
// char		**ft_split(char const *s, char c);
// char		*ft_substr(char const *s, unsigned int start, size_t len);
// int			ft_isalpha(int c);
// char		*ft_strdup(const char *s1);
// size_t		ft_strlen(const char *s);
// void		*ft_memcpy(void *dst, const void *src, size_t n);
// void		*ft_memset(void *b, int c, size_t len);
// int			ft_isdigit(int c);
// int			is_empty(int c);
// int			ft_atoi(const char *str);
// int			ft_strcmp(const char *s1, const char *s2);
// // char		*ft_strchr(const char *s, int c);
// char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

//	UTILS MAP
char		*ft_read_file(int fd);
char		*remove_empty(char *s);
void		init_tmap(t_map *tmap);
void		check_empty_lines(char *s);
int			num_lines(char **arr);
char		*get_iden(char *s);
char		*get_info(char *s);

int			ft_error(char *str, int ex, int ret);
void		clean_arr2d(char **arr2d);

int			check_map(t_map *tmap);
int			closed_map(t_map tmap);

#endif
