/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:50:10 by baltes-g          #+#    #+#             */
/*   Updated: 2023/01/23 15:13:36 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void check_escaped(char *s)
{
	int i = 0;
	int b1 = 1;
	int b2 = 1;

	while(s[i] != '\0')
	{
		if (s[i] == 34)
			b1 *= -1;
		if (s[i] == 39)
			b2 *= -1;
		if (s[i] == 92 && b1 == 1 && b2 == 1)
		{
			ft_memmove(&s[i], &s[i+2], ft_strlen(&s[i+2]));
			s[i+ft_strlen(&s[i+2])] = '\0';
		}
		++i;
	}
}

static int	count_words(char const *s, char c)
{
	int	sum;
	int	in_word;

	sum = 0;
	in_word = 0;
	while (*s != '\0')
	{
		if (*s == 34 && *s != '\0')
		{
			++s;
			while (*s != 34)
				++s;
		}
		if (*s == 39 && *s != '\0')
		{
			++s;
			while (*s != 39)
				++s;
		}
		if (*s != c && in_word == 0)
		{
			++sum;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (sum);
}

static int	word_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == 34)
		{
			len++;
			i++;
			while (s[i] != 34)
			{
				len++;
				i++;
			}
		}
		if (s[i] == 39)
		{
			len++;
			i++;
			while (s[i] != 39)
			{
				len++;
				i++;
			}
		}
		len++;
		i++;
	}
	return (len);
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

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	char	**new;

	check_escaped(s);
	if (*s && *s == '.' && s[1] && s[1] == '/')
	{
		new = malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = ft_substr(s, 0, ft_strlen(s));
		new[1] = NULL;
		return (new);
	}
	new = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_words(s, c))
	{
		while (s[i] == c)
			i++;
		new[j] = ft_substr(s, i, word_len(s, c, i));
		if (new[j][0] == 34 || new[j][0] == 39)
			new[j] = ft_substr(new[j], 1, ft_strlen(new[j])-2);
		write(2, new[j], ft_strlen(new[j]));
		write(2, ";", 1);
		if (!new[j])
			return (malloc_error(new, j));
		i += word_len(s, c, i);
		++j;
	}
	new[j] = (NULL);
	return (new);
}
