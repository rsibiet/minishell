/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_to_norme_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 16:20:48 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/16 13:01:07 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_env_z(char **c, char *ln, int j)
{
	static char		*tp;

	tp = NULL;
	tp = ft_strjoin(ln, " \"");
	ft_strdel(&ln);
	ln = ft_strjoin(tp, c[j + 2]);
	ft_strdel(&tp);
	tp = ft_strjoin(ln, "\" ");
	ft_strdel(&ln);
	ln = ft_strdup(tp);
	ft_strdel(&tp);
	return (ln);
}

void			end_update_cd_2(char *c, t_env *e, int *k, int j)
{
	static char		*s;

	s = gen_pwd_cd(c, e->env[j], 1, k);
	if (ft_strcmp(s, "PWD=") == 0)
		e->env[j] = ft_strjoin(s, "/");
	else
		e->env[j] = ft_strdup(s);
	ft_strdel(&s);
}

void			control_av_echo_2(char *line, char **c, int i, int k)
{
	static char		*tp;
	static char		memo;

	tp = NULL;
	memo = i;
	while (line[i] != '"' && i > 4 &&
			(line[i - 1] != ' ' || line[i - 1] != '\t'))
		i--;
	if (i > 4)
	{
		tp = ft_strdup(c[k]);
		ft_strdel(&(c[k]));
		c[k] = ft_strjoin("\"", tp);
		ft_strdel(&tp);
	}
	i = memo;
}

static void		control_av_echo_4(char *line, char **c, int i, int k)
{
	static char		*tp;
	static char		memo;

	tp = NULL;
	memo = i;
	while (line[i] != 39 && i > 4 &&
			(line[i - 1] != ' ' || line[i - 1] != '\t'))
		i--;
	if (i > 4)
	{
		tp = ft_strdup(c[k]);
		ft_strdel(&(c[k]));
		c[k] = ft_strjoin("\"", tp);
		ft_strdel(&tp);
	}
	i = memo;
}

void			control_av_echo_3(char *line, char **c, int i, int j)
{
	int		k;

	k = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 39)
			j++;
		if (j % 2 == 0 && (line[i] == ' ' || line[i] == '\t') &&
				line[i + 1] != ' ' && line[i + 1] != '\t')
			k++;
		if (j % 2 == 1 && (line[i - 1] == ' ' || line[i - 1] == 39)
				&& line[i] == '~')
			control_av_echo_4(line, c, i, k);
		i++;
	}
}
