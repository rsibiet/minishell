/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 12:18:45 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 19:20:41 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_av_echo(char *line, char **c, int i, int j)
{
	int				k;

	k = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			j++;
		if (j % 2 == 0 && (line[i] == ' ' || line[i] == '\t') &&
			line[i + 1] != ' ' && line[i + 1] != '\t')
			k++;
		if (j % 2 == 1 && (line[i - 1] == ' ' || line[i - 1] == '"')
			&& line[i] == '~')
			control_av_echo_2(line, c, i, k);
		i++;
	}
	control_av_echo_3(line, c, 0, 0);
	ft_strdel(&line);
}

char	*gen_pwd_cd_2(char *s, int i, int len)
{
	static char		*p;

	p = NULL;
	len = ft_strlen(s);
	if (len == 4)
	{
		ft_strdel(&s);
		s = ft_strdup("PWD=/");
	}
	else if (len > 5)
	{
		while (s[len] != '/')
			len--;
		if ((p = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
			malloc_error();
		while (i++ < len)
			p[i - 1] = s[i - 1];
		p[i - 1] = '\0';
		ft_strdel(&s);
		s = ft_strdup(p);
		ft_strdel(&p);
	}
	return (s);
}

void	update_env_cd(t_env *e, char **c, int i, int j)
{
	static char		*cc;
	int				tp;

	cc = NULL;
	if (c[1] != NULL && (ft_strcmp(c[1], "-L") == 0 ||
				ft_strcmp(c[1], "-P") == 0))
		j = 2;
	if (ft_strnequ("./", c[j], 2) == 1)
	{
		i = ft_strlen(c[j]);
		tp = 2;
		if ((cc = (char *)malloc(sizeof(char) * (i - 1))) == NULL)
			malloc_error();
		i = 0;
		while (c[j][tp++] != '\0')
		{
			cc[i] = c[j][tp - 1];
			i++;
		}
		update_env_cd_2(e, cc, -1, 0);
	}
	else if (ft_strcmp(c[j], "-") == 0)
		go_back_cd(e, 0, 0);
	else
		update_env_cd_2(e, c[j], 0, 0);
}
