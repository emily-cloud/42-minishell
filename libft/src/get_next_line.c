/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:49:23 by rlane             #+#    #+#             */
/*   Updated: 2024/06/06 12:43:54 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_str_return_null(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

static char	*extract_chars_after_newline(char *line_buffer)
{
	char	*next_line;
	char	*newline_pos;
	size_t	i;

	newline_pos = ft_strchr(line_buffer, '\n');
	if (!line_buffer || !line_buffer[1] || !newline_pos || !newline_pos[1])
		return (NULL);
	next_line = ft_strdup(&newline_pos[1]);
	if (next_line && *next_line == '\0')
		free_str_return_null(next_line);
	i = 1;
	while (newline_pos[i])
	{
		newline_pos[i] = '\0';
		i++;
	}
	return (next_line);
}

static char	*fill_line_buffer(int fd, char *line_buffer)
{
	ssize_t		bytes_read;
	char		*read_buffer;
	char		*temp;

	read_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buffer)
		return (NULL);
	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		read_buffer[bytes_read] = '\0';
		if (!line_buffer)
			line_buffer = ft_strdup("");
		temp = line_buffer;
		line_buffer = ft_strjoin(temp, read_buffer);
		free(temp);
		if (ft_strchr(read_buffer, '\n'))
			break ;
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	}
	free(read_buffer);
	if (bytes_read == -1)
		return (free_str_return_null(line_buffer));
	return (line_buffer);
}

char	*get_next_line(int fd)
{
	static char	*next_line[MAX_FD];
	char		*line_buffer;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE < 1)
		return (NULL);
	if (next_line[fd] && ft_strchr(next_line[fd], '\n'))
		line_buffer = next_line[fd];
	else
		line_buffer = fill_line_buffer(fd, next_line[fd]);
	if (!line_buffer)
	{
		next_line[fd] = NULL;
		return (NULL);
	}
	next_line[fd] = extract_chars_after_newline(line_buffer);
	return (line_buffer);
}
