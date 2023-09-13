/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:15:33 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/13 15:08:05 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	closed_map(t_pmap tmap)
{
	int	i;
	int	j;

	i = 0;
	while (tmap.map[i])
	{
		j = 0;
		while (tmap.map[i][j])
		{
			if (tmap.map[i][j] != '1' && tmap.map[i][j] != ' ')
			{
				if (!tmap.map[i][j + 1] || is_empty(tmap.map[i][j + 1]))
					return (0);
				if (j == 0 || is_empty(tmap.map[i][j - 1]))
					return (0);
				if (!tmap.map[i + 1][j] || is_empty(tmap.map[i + 1][j]))
					return (0);
				if (i == 0 || is_empty(tmap.map[i - 1][j]))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

char	**get_elements(char *s)
{
	int			i;
	int			len;
	char		**allmap;
	char		**elem;

	allmap = ft_split(s, '\n');
	if (!allmap)
		return (NULL);
	if (num_lines(allmap) < 6)
		ft_error("Error:\n Invalid map!", 1, 0);
	len = 6;
	elem = malloc(sizeof(char *) * (len + 1));
	if (!elem)
		return (ft_error("Error:\n malloc elem!", 1, 0), NULL);
	i = 0;
	while (i < len)
	{
		elem[i] = ft_strdup(allmap[i]);
		i++;
	}
	elem[i] = NULL;
	clean_arr2d(allmap);
	return (elem);
}

t_element	*init_telem(char *map)
{
	t_element	*telem;
	int			i;
	char		**elem;

	elem = get_elements(map);
	if (!elem)
		ft_error("Error\nInvalid elements!", 1, 0);
	telem = malloc (sizeof(t_element) * 7);
	if (!telem)
		ft_error("\n malloc telem!", 1, 0);
	i = 0;
	while (i < 6)
	{
		telem[i].id = get_iden(elem[i]);
		telem[i].info = get_info(elem[i]);
		i++;
	}
	telem[i].id = NULL;
	telem[i].info = NULL;
	clean_arr2d(elem);
	return (telem);
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

void	init_tmap(t_pmap *tmap)
{
	char	*s;
	char	*tmp;
	char	**map;
	int		i;

	s = ft_read_file(tmap->fd);
	if (!s)
		ft_error("Error\nReading map file\n", 1, 0);
	tmap->elem = init_telem(s);
	tmp = ft_strnstr(s, tmap->elem[5].info, ft_strlen(s))
		+ ft_strlen(tmap->elem[5].info);
	if (!tmp)
		ft_error("Error:\n Invalid map!", 1, 0);
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
