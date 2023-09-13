/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:48:09 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/11 17:35:31 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	ft_error(char *str, int ex, int ret)
{
	printf("%s\n", str);
	if (ex != -1)
		exit (ex);
	return (ret);
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
