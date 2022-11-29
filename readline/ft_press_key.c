/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_press_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 13:54:01 by ommadhi           #+#    #+#             */
/*   Updated: 2020/12/02 04:12:39 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void			ft_ctr_d(char **str, int *i)
{
	char		*tmp1;
	char		*tmp2;

	tmp1 = ft_strcut(*str, 0, *i);
	tmp2 = ft_strcut(*str, *i + 1, ft_strlen(*str));
	ft_strdel(str);
	*str = ft_strjoin(tmp1, tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
}

void			ft_cursor_motion(int *i, char *buff, char **str, char *prp)
{
	if (ft_strchr(*str, '\n'))
	{
		ft_alt_up_multi(i, *str, (*(unsigned int*)buff), ft_strlen(prp));
		ft_alt_down_multi(i, *str, (*(unsigned int*)buff), ft_strlen(prp));
	}
	else
	{
		ft_alt_up(i, *str, ft_strlen(prp), (*(unsigned int*)buff));
		ft_alt_down(i, *str, ft_strlen(prp), (*(unsigned int*)buff));
	}
	ft_alt_left_right(*str, i, (*(unsigned int*)buff));
	ft_home_end_line(*str, i, (*(unsigned int*)buff));
	ft_mv_cusror((*(unsigned int*)buff), i, *str);
}

int				ft_press_key(int *i, char *buff, char **str, t_his **ht)
{
	ft_save_cmd((*(unsigned int*)buff), *str);
	ft_paste(str, (*(unsigned int*)buff), i);
	if ((*(unsigned int*)buff) == 4)
		ft_ctr_d(str, i);
	if (buff[0] == 9)
		init_autocmp(str, i);
	if (ht)
		if (((*(unsigned int*)buff) == UP || (*(unsigned int*)buff) == DOWN))
			ft_go_up_down((*(unsigned int*)buff), str, ht);
	ft_del_char(*str, i, (*(unsigned int*)buff));
	ft_charjoin(str, buff, i);
	if ((*(unsigned int*)buff) == UP || *(unsigned int*)buff == DOWN)
		*i = ft_strlen(*str);
	if ((*(unsigned int*)buff) == ENTR)
		return (-1);
	return (0);
}

void			ft_befor_return(char **str, int line, int prplent, int r)
{
	int			i;
	t_xy		xy;

	i = ft_strlen(*str);
	if (ft_strchr(*str, '\n'))
		xy = ft_get_multi(i, prplent, *str);
	else
		xy = ft_get_col_line(i, prplent, *str);
	ft_goto(xy.x, line + xy.y - 1);
	tputs(tgetstr("cd", NULL), 0, ft_putsfd);
	if (r == 4 || g_ctr_c == -1)
	{
		ft_strdel(&g_l.str);
		if (r == 4)
		{
			if (ft_strcmp(g_prp, "(42sh)$> "))
				if (ft_strcmp(g_prp, "herdoc>"))
					ft_putendl_fd("42sh : unexpected end of file", 2);
			(!ft_strcmp("(42sh)$> ", g_prp)) ? g_l.str = ft_strdup("exit") : 0;
		}
		return ;
	}
	ft_putstr("\n");
}
