/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchakir <zchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:00:00 by zchakir           #+#    #+#             */
/*   Updated: 2024/01/01 10:00:00 by zchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
void    print_error(void)
{
    ft_putstr("Error\n");
}

void	print_dict_error(void)
{
	ft_putstr("Dict Error\n");
}

static int	process_args(int argc, char **argv, char **dict_file, char **number) //Gère la validation et l'assignation des arguments
{
	if (argc < 2 || argc > 3)
		return (0);
	if (argc == 3)
	{
		*dict_file = argv[1];
		*number = argv[2];
	}
	else
	{
		*dict_file = "numbers.dict";
		*number = argv[1];
	}
	return (1);
}

static int	process_conversion(char *number, t_dict *dict) // t_dict représente le dictionnaire. C'est défini dans dict.c
{
	char	*normalized_number; 
    // Supprime espaces début/fin
    // Supprime zéros en tête
    // Supprime signe + optionnel
    // Retourne une nouvelle chaîne propre
	char	*result;

	normalized_number = normalize_number(number);
	result = convert_number(normalized_number, dict); // Fonction qui fait la conversion nombre → texte

	free(normalized_number);
	if (!result)
		return (0); // Si conversion échoue, result = NULL
	ft_putstr(result);
	ft_putstr("\n");
	free(result); // Libère la mémoire
	return (1);
}


/*
** Fonction principale du programme
*/
int	main(int argc, char **argv)
{
	t_dict	*dict;		/* Pointeur vers le dictionnaire */
	char	*number;		/* Nombre à convertir */
	char	*dict_file;		/* Nom du fichier dictionnaire */

	/* ÉTAPE 1: Validation et traitement des arguments */
	if (!process_args(argc, argv, &dict_file, &number))
	{
		print_error();		
		return (1);		
	}

	/* ÉTAPE 2: Validation du format du nombre */
	if (!is_valid_number(number))
	{
		print_error();		
		return (1);		
	}

	/* ÉTAPE 3: Chargement du dictionnaire depuis le fichier */
	dict = dict_load(dict_file);
	if (!dict)
	{
		print_dict_error();	
		return (1);		
	}

	/* ÉTAPE 4: Conversion et affichage du résultat */
	if (!process_conversion(number, dict))
	{
		print_dict_error();	
		dict_free(&dict);	/* Libère la mémoire du dictionnaire */
		return (1);		
	}

	/* ÉTAPE 5: Nettoyage et fin du programme */
	dict_free(&dict);		
	return (0);			/* Succès du programme */
}

