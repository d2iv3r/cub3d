/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:48:11 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/20 11:18:51 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	is_mapcharacters(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ')
		return (0);
	return (1);
}

int	check_characters(t_pmap *t)
{
	int	p;

	t->y = 0;
	p = 0;
	while (t->map[t->y])
	{
		t->x = 0;
		while (t->map[t->y][t->x])
		{
			if (!is_mapcharacters(t->map[t->y][t->x]) || p > 1)
				return (0);
			if (t->map[t->y][t->x] == 'N' || t->map[t->y][t->x] == 'S'
				|| t->map[t->y][t->x] == 'E' || t->map[t->y][t->x] == 'W')
			{
				t->pos = t->map[t->y][t->x];
				p++;
			}
			t->x++;
		}
		t->y++;
	}
	if (p == 0)
		return (0);
	return (1);
}

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
				if (!tmap.map[i + 1] || is_empty(tmap.map[i + 1][j]))
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

int	check_map(t_pmap *tmap)
{
	char	*s;

	tmap->fd = open(tmap->file, O_RDONLY);
	if (tmap->fd == -1)
		ft_error("Error:\n Invalide File!", 1, 0);
	if (!check_map_ext(tmap->file))
		ft_error("Error:\n Invalide extension! (.cub)", 1, 0);
	s = ft_read_file(tmap->fd);
	if (!s)
		ft_error("Error:\nReading map file\n", 1, 0);
	tmap->elem = init_telem(s);
	if (!tmap->elem)
		ft_error("Error:\n Invalid elements!", 1, 0);
	check_elements(tmap);
	get_map(tmap, s);
	if (!tmap->map)
		ft_error("Error\nInvalid map!", 1, 0);
	if (!check_characters(tmap))
		ft_error("Error\nInvalid characters!", 1, 0);
	if (!closed_map(*tmap))
		ft_error("Error\nMap not closed!", 1, 0);
	tmap->colums = get_long_line(tmap->map) * GRID;
	tmap->rows = num_lines(tmap->map) * GRID;
	return (1);
}
