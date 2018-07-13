/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_minishell_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 16:18:50 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 14:42:49 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		error_oldpwd(t_env *e)
{
	ft_putendl_fd("OLDPWD empty.", 2);
	ft_strdel(&(e->name));
}

void		error_lstat(char *c)
{
	ft_putstr_fd("PATH: permission denied: ", 2);
	ft_putendl_fd(c, 2);
	exit(0);
}

void		error_op_dir_2(char *c)
{
	ft_putstr_fd("opening of directory ", 2);
	ft_putstr_fd(c, 2);
	ft_putendl_fd(" failed.", 2);
}

void		error_cl_dir_2(char *c)
{
	ft_putstr_fd("closing of directory ", 2);
	ft_putstr_fd(c, 2);
	ft_putendl_fd(" failed.", 2);
}

void		malloc_error(void)
{
	ft_putendl_fd("malloc allocation failed", 2);
	exit(0);
}
