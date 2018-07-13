/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 17:53:01 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/10 14:52:29 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_command_not_found(char *c)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(c, 2);
	exit(0);
}

void	error_op_dir2(char *c)
{
	ft_putstr_fd("Opening of directory ", 2);
	ft_putstr_fd(c, 2);
	ft_putendl_fd(" failed.", 2);
}

void	error_op_dir(t_env *e, int i)
{
	ft_putstr_fd("Opening of directory ", 2);
	ft_putstr_fd(e->path[i], 2);
	ft_putendl_fd(" failed.", 2);
	exit(0);
}

void	error_cl_dir(t_env *e, int i)
{
	ft_putstr_fd("Closing of directory ", 2);
	ft_putstr_fd(e->path[i], 2);
	ft_putendl_fd(" failed.", 2);
	exit(0);
}

void	error_fork(void)
{
	ft_putendl_fd("Fork failed", 2);
	exit(0);
}
