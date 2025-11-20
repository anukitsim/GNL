/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsimint <atsimint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:35:43 by atsimint          #+#    #+#             */
/*   Updated: 2025/11/19 18:14:19 by atsimint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H 

#define GET_NEXT_LINE_H 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 14
#endif

size_t	gnl_strlen(char *str);
const char	*gnl_strchr(const char *s, char c);
void	gnl_concat(char *str1, char *str2, char *joined_str);
char	*gnl_strjoin(char *str1, char *str2);
char	*gnl_substr(char *str, unsigned int index, size_t count);
char	*get_next_line(int fd);

#endif

