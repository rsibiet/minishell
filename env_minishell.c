/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 15:18:25 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 19:37:06 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_unsetenv(t_env *e, int i, int j)
{
	static char		**s;

	j = 0;
	s = NULL;
	if (e->env == NULL)
		ft_putendl("env: unsetenv: No such file or directory");
	else
	{
		while (e->env[j] != NULL)
			j++;
		if ((s = (char **)malloc(sizeof(char *) * j)) == NULL)
			malloc_error();
		j = 0;
		while (j++ < i)
			s[j - 1] = ft_strdup(e->env[j - 1]);
		while (e->env[j] != NULL)
		{
			s[j - 1] = ft_strdup(e->env[j]);
			j++;
		}
		s[j - 1] = NULL;
		ft_strdel_del(&(e->env));
		e->env = ft_strdup_dup(s);
		ft_strdel_del(&s);
	}
}

static void		modify_env_2(t_env *e, char **c, int tp)
{
	static char		**s;
	static char		*cc;

	s = NULL;
	cc = NULL;
	if (ft_strcmp(c[0], "setenv") == 0 && tp == 3)
	{
		cc = ft_strjoin(c[1], "=");
		ft_strdel(&c[1]);
		c[1] = ft_strjoin(cc, c[2]);
		s = ft_strjoin_join(e->env, c[1]);
		ft_strdel_del(&(e->env));
		e->env = ft_strdup_dup(s);
		ft_strdel(&cc);
		ft_strdel_del(&s);
	}
	else if (ft_strcmp(c[0], "setenv") == 0 && tp > 3)
		ft_putendl_fd("setenv: Too many arguments.", 2);
	else if (tp == 1)
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
}

void			modify_env(t_env *e, char **c, int i, int j)
{
	static size_t	n;
	static int		tp;

	tp = mini_compt_c(c);
	if ((ft_strcmp(c[0], "unsetenv") == 0 && c[1] != NULL) ||
		(ft_strcmp(c[0], "setenv") == 0 && tp == 3))
	{
		while (c[j] != NULL)
		{
			n = 0;
			while (c[j][n] != '\0')
				n++;
			while (e->env != NULL && e->env[i] != NULL &&
				ft_strnequ(e->env[i], c[j], n) == 0)
				i++;
			if (e->env == NULL || (e->env[i] != NULL && e->env[i][n] == '='))
				ft_unsetenv(e, i, 0);
			i = 0;
			j++;
		}
	}
	else if (ft_strcmp(c[0], "setenv") == 0 && tp == 2)
		modify_env_3(e, c[1], 0, 0);
	if (e->env != NULL)
		modify_env_2(e, c, tp);
}
