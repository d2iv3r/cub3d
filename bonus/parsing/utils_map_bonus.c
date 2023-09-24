/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:40:39 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/24 14:40:48 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	map_len(char *s)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (is_empty(s[i]) && (s[i + 1] && is_empty(s[i + 1])))
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	check_empty_lines(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n' && (s[i + 1] && s[i + 1] == '\n'))
			ft_error("Error:\n Map must not separated by empty lines!", 1, 0);
		i++;
	}
}

int	num_lines(char **arr)
{
	int	i;

	if (!arr || !*arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	get_pmap(char **map, t_pmap *tmap)
{
	int		i;
	size_t	ll;
	size_t	j;

	tmap->map = malloc(sizeof(char *) * (num_lines(map) + 1));
	if (!tmap->map)
		ft_error("Error: malloc tmap->map!", 1, 0);
	i = 0;
	ll = get_long_line(map);
	while (map[i])
	{
		tmap->map[i] = malloc(sizeof(char) * (ll + 1));
		if (!tmap->map[i])
			ft_error("Error:\n malloc tmap->map[i]!", 1, 0);
		ft_strlcpy(tmap->map[i], map[i], ft_strlen(map[i]) + 1);
		j = ft_strlen(map[i]);
		while (j < ll)
		{
			tmap->map[i][j] = ' ';
			j++;
		}
		tmap->map[i][ll] = 0;
		i++;
	}
	tmap->map[i] = NULL;
}

void	get_map(t_pmap *tmap, char *s)
{
	char	*tmp;
	char	**map;
	int		i;

	tmp = ft_strnstr(s, tmap->elem[5].info, ft_strlen(s))
		+ ft_strlen(tmap->elem[5].info);
	if (!tmp)
		ft_error("Error:\nInvalid map!", 1, 0);
	i = 0;
	while (tmp[i] && tmp[i] == '\n')
		i++;
	check_empty_lines(tmp + i);
	map = ft_split(tmp + i, '\n');
	if (!map || !*map)
		ft_error("Error:\n Invalid map!", 1, 0);
	free(s);
	get_pmap(map, tmap);
	clean_arr2d(map);
}
