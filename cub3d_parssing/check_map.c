/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:48:11 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/11 16:44:58 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_ext(char *mapfile)
{
	char	*ext;

	ext = ft_strrchr(mapfile, '.');
	if (!ext)
		return (0);
	if (ft_strncmp(ext, ".cub", 3) != 0)
		return (0);
	return (1);
}

int	check_elements(t_map tmap)
{
	int	i;

	i = 0;
	while (tmap.elem[i].id)
	{
		if (ft_strcmp(tmap.elem[i].id, "NO")
			&& ft_strcmp(tmap.elem[i].id, "SO")
			&& ft_strcmp(tmap.elem[i].id, "WE")
			&& ft_strcmp(tmap.elem[i].id, "EA")
			&& ft_strcmp(tmap.elem[i].id, "F")
			&& ft_strcmp(tmap.elem[i].id, "C"))
			return (0);
		if (ft_strcmp(tmap.elem[i].id, "C") != 0
			&& ft_strcmp(tmap.elem[i].id, "F") != 0)
		{
			if (open(tmap.elem[i].info, O_RDONLY, 0) == -1)
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_colors(t_map tmap)
{
	int		i;
	char	**tmp;

	i = 0;
	while (tmap.elem[i++].id)
	{
		if (!ft_strcmp(tmap.elem[i].id, "C")
			|| !ft_strcmp(tmap.elem[i].id, "F"))
		{
			tmp = ft_split(tmap.elem[i].info, ',');
			if (!tmp || !tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
				ft_error("Error:\n 3 color RGB!", 1, 0);
			tmap.elem[i].color[0] = ft_atoi(tmp[0]);
			tmap.elem[i].color[1] = ft_atoi(tmp[1]);
			tmap.elem[i].color[2] = ft_atoi(tmp[2]);
			if (tmap.elem[i].color[0] < 0 || tmap.elem[i].color[1] < 0
				|| tmap.elem[i].color[2] < 0)
				return (0);
			if (tmap.elem[i].color[0] > 255 || tmap.elem[i].color[1] > 255
				|| tmap.elem[i].color[2] > 255)
				return (0);
			clean_arr2d(tmp);
		}
	}
	return (1);
}

int	check_characters(char **map)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ')
				return (0);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				p++;
			j++;
		}
		i++;
	}
	if (p > 1 || p == 0)
		return (0);
	return (1);
}

int	check_map(t_map *tmap)
{
	tmap->fd = open(tmap->file, O_RDONLY);
	if (tmap->fd == -1)
		ft_error("Error:\n Invalide File!", 1, 0);
	if (!check_map_ext(tmap->file))
		ft_error("Error:\n Invalide extension! (.cub)", 1, 0);
	init_tmap(tmap);
	if (!check_elements(*tmap))
		return (ft_error("Error:\n Invalid identifier or path!", 1, 0));
	if (!check_colors(*tmap))
		return (ft_error("Error:\n colors in range [0,255]", 1, 0));
	if (!check_characters(tmap->map))
		ft_error("Error:\n Invalid characters in the map!", 1, 0);
	if (!closed_map(*tmap))
		ft_error("Error:\n The map isn't closed!", 1, 0);
	return (1);
}
