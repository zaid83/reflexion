/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchakir <zchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by zchakir           #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by zchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
static int  is_number(char c)
{
    return (c >= '0' && c <= '9');
}

int is_valid_number(char *str)
{
    int i;
    if (!str || *str == '\0')
	return (0);
    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (!is_number(str[i]))
            return (0);
        i++;
    }
    return (1);
}

char	*normalize_number(char *str)
{
	char	*normalized;
	int		i;

	// Vérifier si la chaîne est valide
	if (!str)
		return (NULL);
	i = 0;
	// Ignorer les zéros en début de chaîne
	while (str[i] == '0')
		i++;
	// Si que des zéros, retourner "0"
	if (str[i] == '\0')
		return (ft_strdup("0"));
	// Allouer mémoire pour la chaîne normalisée
	normalized = malloc(ft_strlen(str + i) + 1);
	if (!normalized)
		return (NULL);
	// Copier la partie sans zéros initiaux
	ft_strcpy(normalized, str + i);
	return (normalized);
}