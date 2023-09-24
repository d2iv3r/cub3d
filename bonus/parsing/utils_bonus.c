/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:40:32 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/24 14:40:34 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	ft_error(char *str, int ex, int ret)
{
	printf("%s\n", str);
	if (ex != -1)
		exit (ex);
	return (ret);
}

int	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char *s, char *buff)
{
	int		i;
	int		j;
	char	*str;

	if (!s)
	{
		s = (char *)malloc(1 * sizeof(char));
		if (!s)
			return (NULL);
		s[0] = '\0';
	}
	if (!buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen_gnl(s) + ft_strlen_gnl(buff)) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i] != '\0')
		str[i] = s[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen_gnl(s) + ft_strlen_gnl(buff)] = '\0';
	free(s);
	return (str);
}

char	*ft_read_file(int fd)
{
	char		*s;
	char		*buff;
	int			rdd;

	if (fd == -1)
		return (0);
	rdd = 1;
	s = NULL;
	buff = malloc(sizeof(char) * 2);
	if (!buff)
		return (NULL);
	while (rdd > 0)
	{
		rdd = read(fd, buff, 1);
		if (rdd == -1)
		{
			if (s)
				free(s);
			return (free(buff), NULL);
		}
		buff[rdd] = '\0';
		s = ft_strjoin_gnl(s, buff);
	}
	free(buff);
	return (s);
}

// char	*remove_empty(char *s)
// {
// 	int		i;
// 	char	*res;
// 	int		len;

// 	i = 0;
// 	len = 0;
// 	res = malloc(map_len(s) * sizeof(char) + 1);
// 	if (!res)
// 		exit(1);
// 	i = 0;
// 	len = 0;
// 	while (s[i])
// 	{
// 		if (is_empty(s[i]) && (s[i + 1] && is_empty(s[i + 1])))
// 			i++;
// 		else
// 		{
// 			res[len] = s[i];
// 			len++;
// 			i++;
// 		}
// 	}
// 	res[len] = 0;
// 	free(s);
// 	return (res);
// }
