/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchakir <zchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by zchakir           #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by zchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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



/*Cette fonction ne copie PAS les chaînes,
 elle copie seulement les adresses !*/

t_dict_entry	*create_entry(char *number, char *word)
{
	t_dict_entry	*entry;		// Déclarer un pointeur vers une nouvelle entrée

	// ÉTAPE 1: Allouer la mémoire pour une nouvelle entrée
	entry = malloc(sizeof(t_dict_entry));	// Allouer exactement la taille d'une entrée
	if (!entry)							// Vérifier si malloc a échoué (retourne NULL)
		return (NULL);						// Si échec, retourner NULL pour signaler l'erreur
	
	// ÉTAPE 2: Initialiser les champs de l'entrée
	entry->number = number;					// Assigner le pointeur vers le nombre (ex: "42")
	entry->word = word;						// Assigner le pointeur vers le mot (ex: "forty two")
	entry->next = NULL;						// Initialiser le pointeur suivant à NULL (fin de liste)
	
	// ÉTAPE 3: Retourner l'entrée créée
	return (entry);							// Retourner le pointeur vers la nouvelle entrée
}

t_dict	*dict_load(char *filename)
{
	t_dict	*dict;			// Pointeur vers le dictionnaire à créer
	int		fd;				// Descripteur de fichier (file descriptor)
	char	buffer[1024];	// Buffer pour lire le contenu du fichier
	int		bytes_read;		// Nombre d'octets lus depuis le fichier

	// ÉTAPE 1: Ouvrir le fichier en lecture seule
	fd = open(filename, O_RDONLY);	// Ouvrir le fichier (ex: "numbers.dict")
	if (fd == -1)					// Si ouverture échoue (fichier inexistant, etc.)
		return (NULL);				// Retourner NULL pour signaler l'échec
	
	// ÉTAPE 2: Allouer la mémoire pour le dictionnaire
	dict = malloc(sizeof(t_dict));	// Allouer la structure principale du dictionnaire
	if (!dict)						// Si malloc échoue
	{
		close(fd);					// Fermer le fichier avant de quitter
		return (NULL);				// Retourner NULL pour signaler l'échec
	}
	
	// ÉTAPE 3: Initialiser le dictionnaire vide
	dict->entries = NULL;			// Aucune entrée au début (liste vide)
	
	// ÉTAPE 4: Lire le contenu du fichier
	bytes_read = read(fd, buffer, 1023);	// Lire jusqu'à 1023 octets du fichier
	buffer[bytes_read] = '\0';				// Terminer la chaîne avec le caractère nul
	
	// ÉTAPE 5: Fermer le fichier et retourner
	close(fd);								// Fermer le descripteur de fichier
	// ÉTAPE 6: Parser le buffer et remplir le dictionnaire
	process_buffer(dict, buffer);			// Traiter le contenu ligne par ligne
	
	return (dict);							// Retourner le dictionnaire rempli
}

void	process_buffer(t_dict *dict, char *buffer)
{
	char	*line_start;		// Début de la ligne actuelle
	char	*number;			// Nombre extrait de la ligne
	char	*word;				// Mot extrait de la ligne
	t_dict_entry	*entry;	// Nouvelle entrée créée
	int		i;

	// Parcourir le buffer caractère par caractère
	line_start = buffer;		// Commencer au début du buffer
	i = 0;
	while (buffer[i])			// Tant qu'on n'est pas à la fin
	{
		if (buffer[i] == '\n')	// Si on trouve une fin de ligne
		{
			buffer[i] = '\0';	// Remplacer \n par \0 (terminer la ligne)
			if (parse_line(line_start, &number, &word))	// Parser la ligne
			{
				entry = create_entry(number, word);	// Créer l'entrée
				if (entry)								// Si création réussie
					add_entry(dict, entry);			// Ajouter au dictionnaire
			}
			line_start = buffer + i + 1;			// Passer à la ligne suivante
		}
		i++;
	}
}

void	dict_free(t_dict **dict)
{
	t_dict_entry	*current;
	t_dict_entry	*next;

	if (!dict || !*dict)
		return;
	current = (*dict)->entries;
	while (current)
	{
		next = current->next;
		free(current->number);
		free(current->word);
		free(current);
		current = next;
	}
	free(*dict);
	*dict = NULL;
}

char	*dict_find(t_dict *dict, char *number)
{
	t_dict_entry	*current;

	if (!dict || !number)
		return (NULL);
	current = dict->entries;
	while (current)
	{
		if (ft_strcmp(current->number, number) == 0)
			return (current->word);
		current = current->next;
	}
	return (NULL);
}