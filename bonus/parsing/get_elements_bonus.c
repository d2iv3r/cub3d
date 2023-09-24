/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:38:57 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/24 14:39:58 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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
		ft_error("Error:\nInvalid map!", 1, 0);
	len = 6;
	elem = malloc(sizeof(char *) * (len + 1));
	if (!elem)
		return (ft_error("Error:\nmalloc elem!", 1, 0), NULL);
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

char	*get_iden(char *s)
{
	int		i;
	int		j;
	char	*iden;

	i = 0;
	while (s[i] && is_empty(s[i]))
		i++;
	j = 0;
	while (s[i + j] && !is_empty(s[i + j]))
		j++;
	iden = malloc(sizeof(char) * (j + 1));
	if (!iden)
		ft_error("Error:\n malloc iden!", 1, 0);
	j = 0;
	while (s[i + j] && !is_empty(s[i + j]))
	{
		iden[j] = s[i + j];
		j++;
	}
	iden[j] = 0;
	return (iden);
}

char	*get_info(char *s)
{
	int		i;
	int		j;
	char	*info;

	i = 0;
	while (s[i] && is_empty(s[i]))
		i++;
	while (s[i] && !is_empty(s[i]))
		i++;
	while (s[i] && is_empty(s[i]))
		i++;
	j = 0;
	while (s[i + j])
		j++;
	info = malloc(sizeof(char) * (j + 1));
	if (!info)
		ft_error("Error:\n malloc iden!", 1, 0);
	j = 0;
	while (s[i + j])
	{
		info[j] = s[i + j];
		j++;
	}
	info[j] = 0;
	return (info);
}

t_element	*init_telem(char *map)
{
	t_element	*telem;
	int			i;
	char		**elem;

	elem = get_elements(map);
	if (!elem)
		ft_error("Error:\nInvalid elements!", 1, 0);
	telem = malloc (sizeof(t_element) * 7);
	if (!telem)
		ft_error("Error:\nmalloc telem!", 1, 0);
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
