/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitagaw <mk@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:45:33 by mkitagaw          #+#    #+#             */
/*   Updated: 2021/05/07 09:36:57 by mkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
//int BUFFER_SIZE = 1;
/*
int memo_check(char **line, char **memo)
{
	char	*p_n;
	char *tmp;

	if (*memo)
	{
		p_n = ft_strchr(*memo, '\n');
		if (p_n)
			*p_n = '\0';
		tmp = *line;
		*line = ft_strdup(*memo);
		free(tmp);
		if (*line == NULL)
			return (-1);
		if (p_n)
		{
			free(*memo);
			*memo = ft_strdup(p_n + 1);
			if (*memo == NULL)
				return (-1);
			return (1);
		}
		*memo = NULL;
	}
	return (0);
}

int buf_check(int fd, char **line, char **buf, char **memo)
{
	int		read_size;
	char	*p_n;
//	int BUFFER_SIZE = 64;
	char *tmp;

	read_size = read(fd, *buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		(*buf)[read_size] = '\0';
		p_n = ft_strchr(*buf, '\n');
		if (p_n)
			*p_n = '\0';
		tmp = *line;
		*line = ft_strjoin(tmp, *buf);
		free(tmp);
		if (*line == NULL)
			return (-1);
		if (p_n)
		{
			*memo = ft_strdup(p_n + 1);
			if (*memo == NULL)
				return (-1);
			return (1);
		}
		read_size = read(fd, *buf, BUFFER_SIZE);
	}
	return (read_size);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*memo;
//	int			BUFFER_SIZE = 64;
	int			flag;

	if (line == NULL || fd < 0)
		return (-1);
	*line = malloc(1);
	buf = malloc(BUFFER_SIZE + 1);
	if ((*line == NULL) || (buf == NULL))
		return (-1);
	(*line)[0] = '\0';
	flag = memo_check(line, &memo);
	if (flag != 0)
	{
		free(buf);
		return (flag); 
	}
	flag = buf_check(fd, line, &buf, &memo);
	free(buf);
//	if (flag == '\0')
//		printf("last : %s\n", memo);
	return (flag);
}
*/


int makeline(int fd, char **line, char **memo, char **buf)
{
	char *tmp;
	char *p;
	int	read_size;

	if (*memo)
	{
		p = ft_strchr(*memo, '\n');
		if (p)
		{
			*p = '\0';
			tmp = ft_strdup(*memo);
			if (tmp == NULL)
				return (-1);
		//	if (*line)
		//		free(*line);
			*line = tmp;
		//	free(*memo);
			tmp = ft_strdup(p + 1);
			if (tmp == NULL)
				return (-1);
			free(*memo);
			*memo = tmp;
			return (1);
		}
		else
		{
			tmp = ft_strdup(*memo);
			if (tmp == NULL)
			   return (-1);
		//	free(*line);
			*line = tmp;
			free(*memo);
			*memo = NULL;	
		}
	}

	read_size = read(fd, *buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		(*buf)[read_size] = '\0';
		p = ft_strchr(*buf, '\n');
		if (p)
		{
			*p = '\0';
//			if ((*line)[0] == '\0')
//				tmp = ft_strdup(*buf);
//			else
				tmp = ft_strjoin(*line, *buf);
			if (tmp == NULL)
				return (-1);
			if (*line)
				free(*line);
			*line = tmp;
			tmp  = ft_strdup(p + 1);
			if (tmp == NULL)
				return (-1);
			free(*memo);
			*memo = tmp;
			return (1);
		}
		else
		{
//			if ((*line)[0] == '\0')
//				tmp = ft_strdup(*buf);
//			else
				tmp = ft_strjoin(*line, *buf);
			if (tmp == NULL)
				return (-1);
			if (*line)
				free(*line);
			*line = tmp;
			read_size = read(fd, *buf, BUFFER_SIZE);
		}
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char *memo;
	int flag;
	char *buf;
	int	test[1];

	if ((line == NULL) || (read(fd, test, 0) < 0))
		return (-1);
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (-1);
	*line = malloc(1);
	if (!*line)
		return (-1);
	(*line)[0] = '\0';
	flag = makeline(fd, line, &memo, &buf);
	if (flag != 1)
		free(memo);
	free(buf);
	return (flag);
}
/*
#include <sys/types.h>
#include <stdio.h>

int    main(void)
{
	int        d = 1;
	char    *line;
	int        fd;
	int        i = 1;

	fd = open("sample.txt", O_RDONLY);
	//printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
	while (d == 1)
	{
		printf("---%dline---\n", i);
		d = get_next_line(fd, &line);
		printf("%s\t", line);
		free(line);
		printf("d : %d\n", d);
		i++;
	}
	//d = get_next_line(fd, &line);

	//printf("%s\t", line);

	//printf("d : %d\n", d);

	close(fd);
	system("leaks a.out");

	return (0);

}
*/
