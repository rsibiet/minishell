/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_minishell_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:58:29 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/16 13:00:15 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ft_env_1(char **c, int j, int b)
{
	static char		*tp;
	static char		*ln;

	ln = NULL;
	tp = NULL;
	while (c[j + 2] != NULL)
	{
		if (c[j] != NULL)
			ft_strdel(&c[j]);
		while (c[j + 2][b] != '\0' && c[j + 2][b] != '=')
			b++;
		if (ln == NULL && (c[j + 2][b] != '=' || b == 0 || c[j + 2][0] == '!'))
		{
			tp = ft_strjoin(" \"", c[j + 2]);
			ln = ft_strjoin(tp, "\" ");
			ft_strdel(&tp);
		}
		else if (c[j + 2][b] != '=' || b == 0 || c[j + 2][0] == '!')
			ln = ft_env_z(c, ln, j);
		ft_strdel(&c[j + 2]);
		b = 0;
		j++;
	}
	return (ln);
}

void			ft_env_3(char **c, t_env *e, char **s, int i)
{
	static char		*tp;
	int				j;
	int				k;

	j = 0;
	tp = ft_strjoin(s[0], "=");
	k = ft_strlen(tp);
	ft_strdel_del(&s);
	while (e->env[j] != NULL &&
		ft_strnequ(e->env[j], tp, k) == 0)
		j++;
	if (e->env[j] != NULL)
	{
		ft_strdel(&(e->env[j]));
		e->env[j] = ft_strdup(c[i]);
	}
	else
	{
		s = ft_strdup_dup(e->env);
		ft_strdel_del(&(e->env));
		e->env = ft_strjoin_join(s, c[i]);
		ft_strdel_del(&s);
	}
	ft_strdel(&tp);
}

static void		ft_env_2(char **c, t_env *e, int i, int j)
{
	while (i != -1 && c[j] != NULL)
	{
		while (c[j][i] != '=' && c[j][i] != '\0')
			i++;
		if (c[j][i] == '=')
		{
			j++;
			i = 0;
		}
		else
			i = -1;
	}
	if (j >= 1 && c[j] == NULL)
		end_2_ft_env_2(c, e, 1);
	else
		end_ft_env_2(c, e, 1);
}

static void		ft_env_4(char **c, t_env *e, int j, int k)
{
	static char		*ln;

	while (j > 0 && c[j] != NULL)
	{
		while (c[j][k] != '\0' && c[j][k] != '=')
			k++;
		if (c[j][k] != '=' || k == 0 || c[j][0] == '!')
			j = -2;
		k = 0;
		j++;
	}
	if (j != -1)
	{
		k = 2;
		while (c[k] != NULL)
			ft_putendl(c[k++]);
	}
	ln = ft_env_1(c, 0, 0);
	ft_strdel_del(&(e->env));
	ft_strdel_del(&c);
	if (ln != NULL && j == -1)
		complete_av(e, ln, 0);
	else if (ln != NULL)
		ft_strdel(&ln);
}

void			ft_env(t_env *e, char **c, int i)
{
	if (e->env != NULL && (c[1] == NULL ||
				(ft_strcmp(c[1], "--") == 0 && c[2] == NULL)))
		ft_putendl_endl(e->env);
	else if (e->env != NULL && ft_strcmp(c[1], "-i") == 0)
		ft_env_4(c, e, 2, 0);
	else if (c[1] != NULL && c[1][0] == '-' && c[1][1] != '\0' && c[2] == NULL)
	{
		while (c[1][i] == '-')
			i++;
		if (c[1][i] != '\0')
		{
			ft_putstr_fd("env: illegal option -- ", 2);
			ft_putchar_fd(c[1][i], 2);
			ft_putchar_fd('\n', 2);
			ft_putendl_fd("usage: env [-i] [name=value]", 2);
		}
	}
	else if (e->env != NULL)
		ft_env_2(c, e, 0, 1);
}
