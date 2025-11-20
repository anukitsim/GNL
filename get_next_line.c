/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsimint <atsimint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:50:53 by atsimint          #+#    #+#             */
/*   Updated: 2025/11/19 19:15:20 by atsimint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_find_newline(char **remainder)
{
	const char	*ptr_to_newline;
	char		*line_to_return;

	ptr_to_newline = gnl_strchr(*remainder, '\n');
	if (!ptr_to_newline)
	{
		line_to_return = *remainder;
		*remainder = NULL;
		return (line_to_return);
	}
	return (NULL);
}

static char	*get_line_to_return(char **remainder)
{
	const char	*ptr_to_newline;
	char		*new_remainder;
	char		*line_to_return;
	size_t		len;

	line_to_return = gnl_find_newline(remainder);
	if (line_to_return)
		return (line_to_return);
	ptr_to_newline = gnl_strchr(*remainder, '\n');
	if (!ptr_to_newline)
		return (NULL);
	len = ptr_to_newline - *remainder + 1;
	line_to_return = gnl_substr(*remainder, 0, len);
	if (!line_to_return)
		return (NULL);
	new_remainder = gnl_substr(*remainder, len,
			gnl_strlen(*remainder) - len);
	if (!new_remainder)
	{
		free(line_to_return);
		return (NULL);
	}
	free(*remainder);
	*remainder = new_remainder;
	return (line_to_return);
}


static int	gnl_read_and_join(int fd, char **remainder, char *temp_buff)
{
	char	*new_remainder;
	ssize_t	bytes_read;

	bytes_read = read(fd, temp_buff, BUFFER_SIZE);
	if (bytes_read == 0)
		return (1);
	if (bytes_read == -1)
		return (-1);
	temp_buff[bytes_read] = '\0';
	if (!*remainder)
		new_remainder = gnl_strjoin("", temp_buff);
	else
		new_remainder = gnl_strjoin(*remainder, temp_buff);
	if (!new_remainder)
		return (-1);
	if (*remainder)
		free(*remainder);
	*remainder = new_remainder;
	return (0);
}


static int	gnl_read_loop(int fd, char **remainder)
{
	char	*temp_buff;
	int		result;

	temp_buff = malloc(BUFFER_SIZE + 1);
	if (!temp_buff)
		return (-1);
	while (!*remainder || !gnl_strchr(*remainder, '\n'))
	{
		result = gnl_read_and_join(fd, remainder, temp_buff);
		if (result == -1)
		{
			free(temp_buff);
			return (-1);
		}
		if (result == 1)
			break ;
	}
	free(temp_buff);
	if (*remainder && gnl_strlen(*remainder) == 0)
	{
		free(*remainder);
		*remainder = NULL;
		return (1);
	}
	return (0);
}



char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	int			status;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = gnl_read_loop(fd, &remainder);
	if (status == -1)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	if (!remainder)
		return (NULL);
	line = get_line_to_return(&remainder);
	if (!line)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	return (line);
}

