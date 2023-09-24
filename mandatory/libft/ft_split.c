/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:26:46 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/11 17:36:51 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_ctwrds(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
		{
			i++;
		}
		if (s[i] != '\0' && s[i] != c)
		{
			count ++;
			i++;
		}
		while (s[i] != c && s[i] != '\0')
		{
			i++;
		}
	}
	return (count);
}

static	char	*ft_getstr(char const *s, int *j, char c)
{
	int		len;
	int		start;

	len = 0;
	while (s[*j] != '\0' && s[*j] == c)
		(*j)++;
	start = *j;
	while (s[*j] != '\0' && s[*j] != c)
	{
		(*j)++;
		len++;
	}
	return (ft_substr(s, start, len));
}

static	void	ft_freep(char **p, int *i)
{
	while (*i >= 0)
	{
		free(p[*i]);
		(*i)--;
	}
	free(p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		nw;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	nw = ft_ctwrds(s, c);
	p = (char **)malloc(sizeof(char *) * (nw + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < nw && s[j] != '\0')
	{
		p[i] = ft_getstr(s, &j, c);
		if (p[i] == NULL)
		{
			ft_freep(p, &i);
			return (NULL);
		}
		i++;
	}
	p[i] = NULL;
	return (p);
}
