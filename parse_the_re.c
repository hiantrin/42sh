/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_the_re.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 03:20:30 by hiantrin          #+#    #+#             */
/*   Updated: 2020/01/17 12:50:56 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		trait_the_type(char *file, int out, int type, int ***pipe)
{
	if (type == 1)
	{
		if (type_one(file, &pipe[0], out) == 0)
			return (0);
	}
	else if (type == 2)
	{
		if (type_two(file, &pipe[0], out) == 0)
			return (0);
	}
	else if (type == 3)
	{
		if (type_three(file, &pipe[0], out) == 0)
			return (0);
	}
	else if (type == 4)
	{
		if (type_four(file, &pipe[0], out) == 0)
			return (0);
	}
	return (1);
}

int		type_one(char *file, int ***pipe, int out)
{
	int			b;

	if (help_type_one(file, pipe[0][2]) == 0)
		return (0);
	if ((b = open(file, O_WRONLY | O_TRUNC)) == -1)
		return (print_p_d(file, pipe[0][2]));
	if (out == -1 || out == 1)
	{
		if (pipe[0][1][1] != 1 && pipe[0][1][1] != -1)
			close(pipe[0][1][1]);
		pipe[0][1][1] = b;
	}
	if (out == 2)
	{
		if (pipe[0][2][1] != 2 && pipe[0][2][1] != -1)
			close(pipe[0][2][1]);
		pipe[0][2][1] = b;
	}
	if (out == 0)
	{
		if (pipe[0][0][1] != 0 && pipe[0][0][1] != -1)
			close(pipe[0][0][1]);
		pipe[0][0][1] = b;
	}
	return (1);
}

int		type_two(char *file, int ***pipe, int out)
{
	int b;

	close(open(file, O_CREAT, 0644));
	if ((b = open(file, O_WRONLY | O_APPEND)) == -1)
		return (print_p_d(file, pipe[0][2]));
	if (out == -1 || out == 1)
	{
		if (pipe[0][1][1] != 1 && pipe[0][1][1] != -1)
			close(pipe[0][1][1]);
		pipe[0][1][1] = b;
	}
	if (out == 2)
	{
		if (pipe[0][2][1] != 2 && pipe[0][2][1] != -1)
			close(pipe[0][2][1]);
		pipe[0][2][1] = b;
	}
	if (out == 0)
	{
		if (pipe[0][0][1] != 0 && pipe[0][0][1] != -1)
			close(pipe[0][0][1]);
		pipe[0][0][1] = b;
	}
	return (1);
}

int		type_three(char *file, int ***pipe, int out)
{
	int			b;

	if (error_type_three(file, pipe[0][2]) == 0)
		return (0);
	if ((b = open(file, O_RDONLY)) == -1)
		return (print_p_d(file, pipe[0][2]));
	if (out == -1 || out == 0)
	{
		if (pipe[0][0][1] != 0 && pipe[0][0][1] != -1)
			close(pipe[0][0][1]);
		pipe[0][0][1] = b;
	}
	if (out == 2)
	{
		if (pipe[0][2][1] != 2 && pipe[0][2][1] != -1)
			close(pipe[0][2][1]);
		pipe[0][2][1] = b;
	}
	if (out == 1)
	{
		if (pipe[0][1][1] != 1 && pipe[0][1][1] != -1)
			close(pipe[0][1][1]);
		pipe[0][1][1] = b;
	}
	return (1);
}

int		type_four(char *file, int ***pipe, int out)
{
	int b;

	b = help_redirect(file);
	if (out == -1 || out == 0)
	{
		if (pipe[0][0][1] != 0 && pipe[0][0][1] != -1)
			close(pipe[0][0][1]);
		pipe[0][0][1] = b;
	}
	if (out == 2)
	{
		if (pipe[0][2][1] != 2 && pipe[0][2][1] != -1)
			close(pipe[0][2][1]);
		pipe[0][2][1] = b;
	}
	if (out == 1)
	{
		if (pipe[0][1][1] != 1 && pipe[0][1][1] != -1)
			close(pipe[0][1][1]);
		pipe[0][1][1] = b;
	}
	return (1);
}
