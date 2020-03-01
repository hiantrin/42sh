/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:32:54 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/15 16:34:46 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <unistd.h>
# include <curses.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>

# define MAX_READ   1024

# define CTR_D   4

# define ALT_DOWN   1113266971
# define ALT_UP     1096489755
# define ALT_LEFT   1146821403
# define ALT_RIGHT  1130044187
# define ALT_V      10127586
# define ALT_C      42947
# define ALT_X      8948194
# define UP         4283163
# define RIGHT      4414235
# define DOWN       4348699
# define LEFT       4479771
# define DELETE     127
# define ENTRE      10
# define LAST       4610843
# define FIRST      4741915

typedef struct		s_list
{
	char			*str;
	int				nb_com;
	struct s_list	*next;
}					t_list;

typedef struct		s_mode
{
	int	line;
	int	path;
}					t_mode;

typedef struct		s_key
{
	t_list	*list;

	int		mode;
	int		position;

	char	*line;
	char	*read;
	char	*path;
	char	*lastread;

	int		line_x;
	int		line_y;
	int		line_max;

	int		change;

	int		size;
	int		copy1;
	int		copy2;
	int		x_copy1;
	int		x_copy2;
	int		y_copy1;
	int		y_copy2;

	int		ctrl_d;

	int		alt_x;
	int		alt_c;
	int		alt_v;
	int		alt_left;
	int		alt_right;
	int		alt_up;
	int		alt_down;

	int		right;
	int		left;
	int		up;
	int		down;
	int		all_commande;
	int		max_x;
	int		max_y;
	int		first_x;
	int		first_y;

	int		x;
	int		y;
	int		size_last;
	int		perm_read;
	int		perm_aff;
	int		entre;
	int		delete;
	int		last;
	int		first;
}					t_key;

t_list				*list_past(t_list *list, int mode);
t_list				*list_stock(t_list	*list);

t_key				*return_position_cursor(t_key *key, int mode);
t_key				*save_position(t_key *key, int per);
t_key				*cursor_first_pos(t_key *key);
t_key				*keybord_active(t_key *key);
t_key				*key_last_modification(t_key *key);

int					out(int mode, t_key *key);
int					we_have_signal(int permission);
int					plus_center_char(t_key *key);
int					len_lastline(char *line);
int					cont_newline(char *line);

void				generateur(t_key *k, int per);
void				manger_error(void);
void				change_configuration_term(int mode);
void				plus_char(t_key *key);
void				return_cursor(t_key *key, int position_cursor);
void				delete_select(t_key *key);
void				past_select(t_key *key);
void				alt_up_down(t_key *key);
void				save_historique(char *line, int mode);
void				first_last_line(t_key *key);
void				clean(t_key *key);
void				clean_last_line(t_key *key);
void				alt_left_right(t_key *key);
void				cursor_le(t_key *key);
void				cursor_r(t_key *key);
void				delete_char(t_key *key);
void				mode_copy(t_key *key);
void				cursor_up_down(t_key *key, int zero);

char				*ft_readline(char *path);

#endif
