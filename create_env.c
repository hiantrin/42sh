/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 10:26:39 by hiantrin          #+#    #+#             */
/*   Updated: 2020/01/17 12:47:10 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_env_list	*create_env(char **environ)
{
	t_env_list	*head;
	t_env_list	*env;
	t_env_list	*next;
	int			i;

	i = 0;
	env = create_next(environ[i]);
	head = env;
	if (environ[i])
		i++;
	while (environ[i])
	{
		next = create_next(environ[i]);
		env->next = next;
		env = env->next;
		i++;
	}
	return (head);
}

t_env_list	*create_next(char *environ)
{
	t_env_list	*env;

	if (environ == NULL)
		env = NULL;
	else
	{
		env = (t_env_list *)malloc(sizeof(t_env_list));
		env->name = get_name(environ);
		env->environ = get_environ(environ);
		env->next = NULL;
	}
	return (env);
}

char		*get_name(char *environ)
{
	char	*str;
	int		i;

	i = 0;
	while (environ[i] && environ[i] != '=')
		i++;
	str = ft_strsub(environ, 0, i);
	return (str);
}

char		*get_environ(char *environ)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	while (environ[j] && environ[j] != '=')
		j++;
	j++;
	i = j;
	while (environ[i])
		i++;
	str = ft_strsub(environ, j, i - j);
	return (str);
}

char		*concate(char *path, char *str)
{
	char	*new;
	char	*ptr;

	new = ft_strjoin(path, "/");
	ptr = new;
	new = ft_strjoin(new, str);
	free(ptr);
	return (new);
}
