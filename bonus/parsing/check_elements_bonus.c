/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:24:58 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/24 14:38:04 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	is_texture(char *id)
{
	if (!ft_strcmp(id, "NO") || !ft_strcmp(id, "SO") || !ft_strcmp(id, "WE")
		|| !ft_strcmp(id, "EA"))
		return (1);
	return (0);
}

int	is_identifier(char *id)
{
	if (ft_strcmp(id, "NO") && ft_strcmp(id, "SO") && ft_strcmp(id, "WE")
		&& ft_strcmp(id, "EA") && ft_strcmp(id, "C") && ft_strcmp(id, "F"))
		return (0);
	return (1);
}

int	check_ident(t_element *elem, int *arr)
{
	int	i;

	i = -1;
	while (elem[++i].id)
	{
		if (!is_identifier(elem[i].id))
			return (0);
		if (!ft_strcmp(elem[i].id, "NO"))
			arr[0]++;
		if (!ft_strcmp(elem[i].id, "SO"))
			arr[1]++;
		if (!ft_strcmp(elem[i].id, "WE"))
			arr[2]++;
		if (!ft_strcmp(elem[i].id, "EA"))
			arr[3]++;
		if (!ft_strcmp(elem[i].id, "F"))
			arr[4]++;
		if (!ft_strcmp(elem[i].id, "C"))
			arr[5]++;
	}
	i = -1;
	while (++i < 6)
		if (arr[i] != 1)
			return (0);
	return (1);
}

int	check_colors(t_element *elem)
{
	int		i;
	char	**tmp;

	i = -1;
	while (elem[++i].id)
	{
		if (!ft_strcmp(elem[i].id, "C")
			|| !ft_strcmp(elem[i].id, "F"))
		{
			tmp = ft_split(elem[i].info, ',');
			if (!tmp || !tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
				return (0);
			elem[i].color[0] = ft_atoi(tmp[0]);
			elem[i].color[1] = ft_atoi(tmp[1]);
			elem[i].color[2] = ft_atoi(tmp[2]);
			if (elem[i].color[0] < 0 || elem[i].color[1] < 0
				|| elem[i].color[2] < 0)
				return (0);
			if (elem[i].color[0] > 255 || elem[i].color[1] > 255
				|| elem[i].color[2] > 255)
				return (0);
			clean_arr2d(tmp);
		}
	}
	return (1);
}

void	check_elements(t_pmap *tmap)
{
	int		i;
	int		arr[6];
	char	*png;

	i = -1;
	while (++i < 6)
		arr[i] = 0;
	if (!check_ident(tmap->elem, arr))
		ft_error("Error\nInvalid Identifier!", 1, 0);
	if (!check_colors(tmap->elem))
		ft_error("Error\nInvalid (R,G,B) colors!", 1, 1);
	i = 0;
	while (tmap->elem[i].id)
	{
		if (is_texture(tmap->elem[i].id))
		{
			png = ft_strrchr(tmap->elem[i].info, '.');
			if (!png || ft_strcmp(png, ".png"))
				ft_error("Error\nTexture must be (.png)", 1, 0);
			if (open(tmap->elem[i].info, O_RDONLY) == -1)
				ft_error("Error\nInvalid texture path!", 1, 0);
		}
		i++;
	}
}
