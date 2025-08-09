/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchakir <zchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by zchakir           #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by zchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>

// Comparer deux chaînes
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

// Calculer la longueur d'une chaîne
int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

// Copier une chaîne
char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// Dupliquer une chaîne
char	*ft_strdup(char *src)
{
	char	*dup;
	int		len;

	len = ft_strlen(src);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strcpy(dup, src);
	return (dup);
}

// Afficher une chaîne
void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}