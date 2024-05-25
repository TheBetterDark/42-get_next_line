/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:22:01 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/16 23:09:32 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Function Declarations
char	*get_next_line_and_update(char **file_content_ptr);
char	*append_read(char *file_content, char *buffer);
void	*read_file(int fd, char **file_content);
char	*get_next_line(int fd);

// Function Definitions
char	*get_next_line(int fd)
{
	static char	*file_content;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!file_content)
	{
		file_content = malloc(1);
		if (!file_content)
			return (NULL);
		file_content[0] = '\0';
	}
	temp = read_file(fd, &file_content);
	if (temp == NULL || file_content[0] == '\0')
	{
		if (file_content)
		{
			free(file_content);
			file_content = NULL;
		}
		return (NULL);
	}
	file_content = temp;
	return (get_next_line_and_update(&file_content));
}

void	*read_file(int fd, char **file_content)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*new_str;
	ssize_t		bytes_read;

	new_str = NULL;
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		new_str = append_read(*file_content, buffer);
		free(*file_content);
		*file_content = new_str;
	}
	buffer[0] = '\0';
	return (*file_content);
}

char	*get_next_line_and_update(char **file_content_ptr)
{
	char	*line_end;
	char	*line;
	char	*new_str;

	line_end = ft_strchr(*file_content_ptr, '\n');
	if (!line_end)
		line_end = ft_strchr(*file_content_ptr, '\0');
	line = ft_substr(*file_content_ptr, 0, line_end - *file_content_ptr + 1);
	if (*line_end == '\n')
		new_str = ft_strdup(line_end + 1);
	else
		new_str = NULL;
	free(*file_content_ptr);
	*file_content_ptr = new_str;
	if ((!line || line[0] == '\0') && (!new_str || new_str[0] == '\0'))
	{
		if (line)
			free(line);
		if (new_str)
			free(new_str);
		*file_content_ptr = NULL;
		return (NULL);
	}
	return (line);
}

char	*append_read(char *file_content, char *buffer)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new_str = malloc((ft_strlen(file_content) + ft_strlen(buffer)) + 1);
	if (!new_str)
	{
		free(file_content);
		return (NULL);
	}
	while (file_content && file_content[i])
	{
		new_str[i] = file_content[i];
		i++;
	}
	while (buffer && buffer[j])
	{
		new_str[i + j] = buffer[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}
