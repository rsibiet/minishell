/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_minishell_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 12:11:38 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 15:07:07 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_wrong_pwd(char *c)
{
	ft_putstr_fd("Home not valid: ", 2);
	ft_putendl_fd(c, 2);
}

void	error_chdir_2(char *c)
{
	ft_putstr_fd("cd: string not in pwd: ", 2);
	ft_putendl_fd(c, 2);
}

void	error_chdir(char *c, int i)
{
	DIR				*d;
	t_dir			*dir;
	static char		cwd[200];
	static char		**s;
	int				j;

	s = ft_strsplit(c, '/');
	j = mini_compt_c(s);
	if ((d = opendir(getcwd(cwd, 199))) == NULL)
		error_op_dir_2(cwd);
	else
	{
		while ((dir = readdir(d)) != NULL && i != 1)
		{
			if (ft_strcmp(dir->d_name, s[j - 1]) == 0)
				error_cd_perm(s[j - 1]);
			if (ft_strcmp(dir->d_name, s[j - 1]) == 0)
				i = 1;
		}
		if (closedir(d) == -1)
			error_cl_dir_2(cwd);
		else if (i == 0)
			error_cd_no_file(s[j - 1]);
	}
	ft_strdel_del(&s);
}

void	error_home(void)
{
	ft_putendl_fd("HOME not set", 2);
}

void	error_pwd(t_env *e)
{
	ft_putendl_fd("No pwd found.", 2);
	ft_strdel(&(e->name));
}
