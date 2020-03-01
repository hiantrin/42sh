/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:09:47 by hiantrin          #+#    #+#             */
/*   Updated: 2020/03/01 19:05:29 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// char    *dtab_to_otab(char **str)
// {
//     char    *new;
//     int     i;
// 	int		size;
// 	int		j;
// 	int		a;

// 	size = size_char_2d(str);
// 	new = malloc(sizeof(char) * size);
// 	new[size] = '\0';
// 	i = 0;
// 	a = 0;
// 	while (str[i])
// 	{
// 		j = 0;
// 		while (str[i][j])
// 			new[a++] = str[i][j++];
// 		if (str[i + 1])
// 			new[a++] = ' ';
// 		i++;
// 	}
// 	return (new);
// }

// int		size_char_2d(char **str)
// {
// 	int     i;
// 	int		size;

// 	i = 0;
// 	size = 0;
// 	while (str[i])
// 	{
// 		size = size + ft_strlen(str[i]);
// 		i++;
// 	}
// 	size = size + i;
// 	return (size);
// }

char	*filter_for_file(char *file, t_list *list)
{
	t_env_list	*env;
	int			i;
	char		**command;
	t_env_list		*next;

	i = 0;
	command = my_magic(list);
	env = create_env(command);
	free(command);
	file = replace_with_env(file, env, i);
	file = replace_home(file, env);
	file = move_slash(file);
	file = move_quote(file, 0);
	while (env != NULL)
	{
		free(env->name);
		free(env->environ);
		next = env->next;
		free(env);
		env = next;
	}
	return (file);
}