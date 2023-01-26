/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:50:10 by baltes-g          #+#    #+#             */
/*   Updated: 2023/01/26 11:35:45 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isscaped(char *s)
{
	int	count;

	count = 0;
	if (*(s - 1))
		s--;
	else
		return (0);
	while (*(s - count) && *(s - count) == 92)
		count++;
	if (count % 2)
		return (*(s + 1));
	return (0);
}

static int	ft_isquote(char *s, char quote)
{
	if (*s != quote)
		return (0);
	if (!ft_isscaped(s))
		return (*s);
	return (0);
}

static void	ft_check_escaped(char *str)
{
	int	i;

	while (*str != '\0')
	{
		if ((*str == 34 || *str == 39) && ft_isscaped(str))
		{
			i = 0;
			while (str[i] != '\0')
			{
				str[i - 1] = str[i];
				++i;
			}
			str[i - 1] = '\0';
		}
		++str;
	}
}

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
	int		words;

	if (*s && *s == '.' && s[1] && s[1] == '/')
		return (ft_split_exe(s));
	words = count_words(s, c);
	new = malloc(sizeof(char *) * (words + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (j < words)
	{
		while (s[i] == c)
			i++;
		new[j] = ft_substr(s, i, word_len(&s[i], c));
		if (new[j][0] == 34 || new[j][0] == 39)
			new[j] = ft_substr(new[j], 1, ft_strlen(new[j]) - 2);
		ft_check_escaped(new[j]);
		if (!new[j])
			return (malloc_error(new, j));
		i += word_len(&s[i], c);
		++j;
	}
	new[j] = (NULL);
	return (new);
}
