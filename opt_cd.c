/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 15:48:37 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 19:45:35 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			update_path(t_env *e, int i)
{
	static char		**s;

	s = NULL;
	while (e->env != NULL && e->env[i] != NULL &&
		ft_strnequ(e->env[i], "PATH=", 5) == 0)
		i++;
	if (e->env != NULL && e->env[i] != NULL)
	{
		if (e->path != NULL)
			ft_strdel_del(&(e->path));
		s = ft_strsplit(e->env[i], '=');
		if (s[1] != NULL)
			e->path = ft_strsplit(s[1], ':');
		ft_strdel_del(&s);
	}
}

static void		dp_slink(char *c, int nchar, int size)
{
	static char		*buff;

	if ((buff = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		malloc_error();
	while ((nchar = readlink(c, buff, size)) < 0)
	{
		ft_strdel(&buff);
		size *= 2;
		if ((buff = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
			malloc_error();
	}
	ft_strdel(&c);
	c = ft_strdup(buff);
	ft_strdel(&buff);
}

char			*opt_cd(char *c, char *op)
{
	t_stat			s;

	if (op == NULL || (ft_strcmp(op, "-L") == 1 && ft_strcmp(op, "-P") == 1))
		return (c);
	if (ft_strcmp(op, "-P") == 0)
	{
		if (lstat(c, &s) == -1)
		{
			ft_putstr_fd("cd: permission denied: ", 2);
			ft_putendl_fd(c, 2);
			return (NULL);
		}
		if (S_ISLNK(s.st_mode))
			dp_slink(c, 0, 64);
	}
	return (c);
}
