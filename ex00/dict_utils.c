/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchakir <zchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by zchakir           #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by zchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

typedef struct s_dict_entry
{
	char				*number;
	char				*word;
	struct s_dict_entry	*next;
}	t_dict_entry;

typedef struct s_dict
{
	t_dict_entry	*entries;
}	t_dict;

int	find_colon(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ':')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_number(char *line, int colon_pos)
{
	char	*number;
	int		i;

	number = malloc(colon_pos + 1);
	if (!number)
		return (NULL);
	i = 0;
	while (i < colon_pos)
	{
		number[i] = line[i];
		i++;
	}
	number[i] = '\0';
	return (number);
}

char	*extract_word(char *line, int colon_pos)
{
	char	*word;
	int		i;
	int		j;
	int		word_len;

	i = colon_pos + 1;
	while (line[i] == ' ')
		i++;
	word_len = ft_strlen(line + i);
	word = malloc(word_len + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (line[i])
	{
		word[j] = line[i];
		i++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

int	parse_line(char *line, char **number, char **word)
{
	int	colon_pos;

	colon_pos = find_colon(line);
	if (colon_pos == -1)
		return (0);
	*number = extract_number(line, colon_pos);
	if (!*number)
		return (0);
	*word = extract_word(line, colon_pos);
	if (!*word)
	{
		free(*number);
		return (0);
	}
	return (1);
}