/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitagaw <mk@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:45:33 by mkitagaw          #+#    #+#             */
/*   Updated: 2021/05/06 10:33:12 by mkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "get_next_line.h"
#include <stdio.h>
int	BUFFER_SIZE = 1;

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;

	if ((s1 == NULL) || (s2 == NULL))
		return (NULL);
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (p == NULL)
		return (NULL);
	*p = '\0';
	ft_strcat(p, s1);
	ft_strcat(p, s2);
	return (p);
}


char	*ft_strchr(const char *s, int c)
{
	char	cc;
	int		len;
	int		i;

	i = 0;
	cc = (char)c;
	len = ft_strlen(s);
	while (len + 1 - i)
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	char	*p;

	p = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!p)
		return (NULL);
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int join_and_split(char **line, char **src, char **next_address)
{
	char *tmp;
	char *n_point;

	*n_point = ft_strchr(*line, '\n');
	if (n_point)
		*n_point = '\0';
	tmp = *line;
	*line = ft_strjoin(tmp, *src);
	if (*line == NULL)
		return (-1);
	free(tmp);
	free(*next_address);
	*next_address = ft_strdup(n_point + 1);
	if (*next_address == NULL)
		return (-1);
	return (1);
}

int makeline(int fd, char **line, char **buf, char **memo)
{
	int	read_size;

	if (*memo && join_and_split(line, memo, memo))
		return (1);
	read_size = read(fd, *buf, BUFFER_SIZE);
	buf[read_size] = '\0';
	while (read_size > 0)
	{
		if(join_and_split(line, &buf, &memo))
			return (1);
		read_size = read(fd, *buf, BUFFER_SIZE);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*memo;
	char		*buf;
	int			flag;

	if ((line == NULL) || fd < 0)
		return (-1);
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (-1);
	if (*line)
		(*line)[0] = '\0';
	flag = makeline(fd, line, &buf, &memo);
	free(buf);
	if (flag == 0)
		free(memo);
	return (flag);
}

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
//	system("leaks a.out");
	return (0);
}

