/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitagaw <mk@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:38:14 by mkitagaw          #+#    #+#             */
/*   Updated: 2021/05/07 08:31:17 by mkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	int	i;

	p = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{	
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
