/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsimint <atsimint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:29:38 by atsimint          #+#    #+#             */
/*   Updated: 2025/11/14 15:14:36 by atsimint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

const char	*gnl_strchr(const char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

void	gnl_concat(char *str1, char *str2, char *joined_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str1[i] != '\0')
	{
		joined_str[i] = str1[i];
		i++;
	}
	while (str2[j] != '\0')
	{
		joined_str[i] = str2[j];
		i++;
		j++;
	}
	joined_str[i] = '\0';
}

char	*gnl_strjoin(char *str1, char *str2)
{
	size_t	str1_len;
	size_t	str2_len;
	char	*joined_str;

	if (!str1)
		str1 = "";
	if (!str2)
		return (NULL);
	str1_len = gnl_strlen(str1);
	str2_len = gnl_strlen(str2);
	joined_str = malloc(str1_len + str2_len + 1);
	if (!joined_str)
		return (NULL);
	gnl_concat(str1, str2, joined_str);
	return (joined_str);
}

char	*gnl_substr(char *str, unsigned int index, size_t count)
{
	size_t	str_len;
	size_t	copy_bytes;
	size_t		j;
	char	*substring;

	j = 0;
	if (!str)
		return (NULL);
	str_len = gnl_strlen(str);
	if (index > str_len)
		return (NULL);
	copy_bytes = count;
	if ((str_len - index) < count)
		copy_bytes = str_len - index;
	substring = malloc(copy_bytes + 1);
	if (!substring)
		return (NULL);
	while (j < copy_bytes)
	{
		substring[j] = str[index];
		j++;
		index++;
	}
	substring[j] = '\0';
	return (substring);
}