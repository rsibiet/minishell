/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_minishell.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 16:46:34 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 19:40:56 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			define_av(t_env *e, char **c, int i, int j)
{
	if (e->av != NULL)
		ft_strdel_del(&(e->av));
	if (ft_strcmp(c[0], "env") != 0 && ft_strcmp(c[0], "setenv") != 0
			&& ft_strcmp(c[0], "unsetenv") != 0)
	{
		while (c[i] != NULL)
			i++;
		if ((e->av = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
			malloc_error();
		while (c[j] != NULL)
		{
			e->av[j] = ft_strdup(c[j]);
			j++;
		}
		e->av[j] = NULL;
	}
}

static void		ft_cd_home_2(int k, char **c, t_env *e)
{
	static char		*u;

	u = opt_cd(c[k], c[1]);
	if (u != NULL)
	{
		ft_strdel(&c[k]);
		c[k] = ft_strdup(u);
		if (chdir(c[k]) == -1)
			error_wrong_pwd(c[k]);
		else if (e->env != NULL)
			update_env_cd(e, c, 0, 1);
	}
}

void			ft_cd_home(t_env *e, int j, int k, char **c)
{
	static char		**s;
	static char		*u;

	s = NULL;
	u = NULL;
	if (e->home != NULL)
	{
		s = ft_strsplit(e->home, '=');
		if (c[1] != NULL && c[1][0] != '~')
			k = 2;
		if (c[k] != NULL)
		{
			j = ft_strlen(c[k]);
			u = ft_strsub(c[k], 1, j - 1);
			ft_strdel(&c[k]);
			c[k] = ft_strjoin(s[1], u);
			ft_strdel(&u);
		}
		else
			c[k] = ft_strdup(s[1]);
		ft_strdel_del(&s);
		ft_cd_home_2(k, c, e);
	}
	else
		ft_putendl_fd("cd: HOME not set", 2);
}

static char		*ft_find_command_2(char *tp, t_env *e)
{
	t_stat			s;
	static char		*c;

	c = ft_strjoin(tp, e->name);
	ft_strdel(&tp);
	if (lstat(c, &s) == -1)
		error_lstat(c);
	if (S_ISDIR(s.st_mode))
	{
		if (!(s.st_mode & S_IXUSR))
			error_lstat(c);
	}
	return (c);
}

char			*ft_find_command(t_env *e, int i, char *c)
{
	DIR			*rep;
	static char	*tp;
	t_dir		*file;

	tp = NULL;
	while (e->path[i++] != NULL)
	{
		if ((rep = opendir(e->path[i - 1])) == NULL)
			error_op_dir(e, i - 1);
		if (rep != NULL)
		{
			while ((file = readdir(rep)) != NULL)
			{
				if (ft_strcmp(file->d_name, e->name) == 0)
				{
					tp = ft_strjoin(e->path[i - 1], "/");
					c = ft_find_command_2(tp, e);
					return (c);
				}
			}
			if (closedir(rep) == -1)
				error_cl_dir(e, i - 1);
		}
	}
	return (c);
}
