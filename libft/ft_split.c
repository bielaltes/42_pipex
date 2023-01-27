/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:50:10 by baltes-g          #+#    #+#             */
/*   Updated: 2023/01/27 11:39:34 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_len(char *str, char c)
{
	int	util;
	int	len;

	len = 0;
	util = ft_isquote(str, 34) | ft_isquote(str, 39);
	if (util)
	{
		++len;
		while (*++str && !ft_isquote(str, util))
			++len;
		if (*str == 34 || *str == 39)
			len++;
	}
	else
	{
		++len;
		while (*++str && *str != c && !ft_isquote(str, 34)
			&& !ft_isquote(str, 39))
			++len;
	}
	return (len);
}

static int	count_words(char *s, char c)
{
	int	sum;
	int	aux;

	sum = 0;
	while (*s != '\0')
	{
		while (*s == c)
			++s;
		aux = word_len(s, c);
		s += aux;
		sum++;
	}
	return (sum);
}

static char	**malloc_error(char **new, int j)
{
	while (j >= 0)
	{
		free(new[j]);
		--j;
	}
	free(new);
	return (NULL);
}

static char	**ft_split_exe(char *s)
{
	char	**new;

	if (count_words(s, ' ') > 1)
		return (NULL);
	new = malloc(sizeof(char *) * 2);
	if (!new)
		return (NULL);
	new[0] = ft_substr(s, 0, ft_strlen(s));
	ft_check_escaped(new[0]);
	new[1] = NULL;
	return (new);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	char	**new;

	if (*s && *s == '.' && s[1] && s[1] == '/')
		return (ft_split_exe(s));
	new = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < count_words(s, c))
	{
		while (s[i] == c)
			++i;
		new[j] = ft_substr(s, i, word_len(&s[i], c));
		if (!new[j])
			return (malloc_error(new, j));
		if (new[j][0] == 34 || new[j][0] == 39)
			new[j] = ft_substr(new[j], 1, ft_strlen(new[j]) - 2);
		ft_check_escaped(new[j]);
		i += word_len(&s[i], c);
	}
	new[j] = (NULL);
	return (new);
}
