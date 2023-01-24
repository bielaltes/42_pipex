/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:50:10 by baltes-g          #+#    #+#             */
/*   Updated: 2023/01/24 12:15:07 by baltes-g         ###   ########.fr       */
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
		if (s[i] == 92)
		{
			ft_memmove(&s[i], &s[i+1], ft_strlen(&s[i+1]));
			s[i+ft_strlen(&s[i+1])] = '\0';
		}
		++i;
	}
}

static int	count_words(char const *s, char c)
{
	int	sum;
	int	in_word;
	int i = 0;

	sum = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 34 && (i == 0 || (i>0 && s[i-1] != '\\')))
		{
			++i;
			while (s[i] != '\0' && s[i] != 34 && s[i-1] != '\\')
				++i;
		}
		if (s[i] == 39 && (i == 0 || (i>0 && s[i-1] != '\\')))
		{
			++i;
			while ( s[i] != '\0'&& s[i] != 39 && s[i-1] != '\\')
				++i;
		}
		if (s[i] != c && in_word == 0)
		{
			++sum;
			in_word = 1;
			++i;
		}
		else if (s[i]== c && (i == 0 || (i>0 && s[i-1] != '\\')))
		{
			in_word = 0;
			++i;
		}
		else
			++i;
	}
	return (sum);
}

static int	word_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != '\0' && s[i] != c && (i==0 || s[i-1] != '\\'))
	{
		if (s[i] == 34 && (i == 0 || (s[i-1] != '\\')))
		{
			len++;
			i++;
			while (s[i] != 34 || s[i-1] == '\\')
			{
				len++;
				i++;
			}
		}
		if (s[i] == 39 && (i == 0 || (s[i-1] != '\\')))
		{
			len++;
			i++;
			while (s[i] != 39 || s[i-1] == '\\')
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

	//check_escaped(s);
	if (*s && *s == '.' && s[1] && s[1] == '/')
	{
		new = malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = ft_substr(s, 0, ft_strlen(s));
		new[1] = NULL;
		return (new);
	}
	//write(2, s, ft_strlen(s));
	//write(2, "\n", 1);
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
		check_escaped(new[j]);
		if (new[j][0] == 34 || new[j][0] == 39)
			new[j] = ft_substr(new[j], 1, ft_strlen(new[j])-2);
		//write(2, new[j], ft_strlen(new[j]));
		//write(2, ";", 1);
		if (!new[j])
			return (malloc_error(new, j));
		i += word_len(s, c, i);
		++j;
	}
	new[j] = (NULL);
	return (new);
}
