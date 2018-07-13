/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 17:42:40 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/16 13:02:21 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <time.h>
# include <sys/resource.h>
# include <signal.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

typedef struct dirent	t_dir;
typedef struct stat		t_stat;

typedef struct	s_env
{
	int			status;
	char		*name;
	char		**env;
	char		**env2;
	char		**av;
	char		**path;
	char		*pwd;
	char		*oldpwd;
	char		*home;
}				t_env;

typedef	struct	s_av
{
	char		**c;
	int			len;
	int			i;
}				t_av;

/*
** Fonctions in recov_env_minishell file
*/

void			ft_execute(t_env *e);
void			sig_handler(int signo);

/*
** Fonctions in recov_env_minishelli_2 file
*/

void			create_basic_env(t_env *e, char *pwd, char host[100]);
void			copy_env(char **envp, t_env *e, size_t i);
void			fork_loop(t_env *e, pid_t pid, char *line);

/*
** Fonctions in find_command_minishell file
*/

void			define_av(t_env *e, char **c, int i, int j);
void			ft_cd_home(t_env *e, int i, int j, char **c);
char			*ft_find_command(t_env *e, int i, char *c);

/*
** Fonctions in find_command_minishell_2 file
*/

void			complete_av(t_env *e, char *line, int i);

/*
** Fonctions in env_minishell file
*/

void			ft_unsetenv(t_env *e, int i, int j);
void			modify_env(t_env *e, char **c, int i, int j);

/*
** Fonctions in env_minishell_2 file
*/

void			ft_env_3(char **c, t_env *e, char **s, int j);
void			ft_env(t_env *e, char **c, int i);

/*
** Fonctions in env_minishell_3 file
*/

void			end_2_ft_env_2(char **c, t_env *e, int i);
void			end_ft_env_2(char **c, t_env *e, int i);

/*
** Fonctions in define_av file
*/

void			mini_ft_split_quote(char *line, int j, int *k, t_av *av);

/*
** Fonctions in define_av_2 file
*/

int				test_exit(t_env *e, int i);
int				remove_multiples_quotes(char *line, int i, int j, int k);
void			control_var_setenv(t_env *e, char **c, int i, int tp);
void			complete_av_2(t_env *e, int i);

/*
** Fonctions in define_av_3 file
*/

char			**split_semicolon(char *line, int i, int j, int tp);
char			**ft_split_quote(char *line, int k);
void			mini_malloc_av(t_av *av);

/*
** Fonctions in define_av_4 file
*/

void			complete_av_6(t_env *e, int i, int len, int j);
void			modify_env_3(t_env *e, char *c, int i, int len);
void			complete_av_5(t_env *e, int i, int len);
void			complete_av_4(t_env *e, int i);
void			complete_av_3(t_env *e, int i, int len);

/*
** Fonctions in opt_cd file
*/

void			update_path(t_env *e, int i);
char			*opt_cd(char *c, char *op);

/*
** Fonctions in update_env file
*/

void			control_av_echo(char *line, char **c, int i, int j);
char			*gen_pwd_cd_2(char *s, int i, int len);
void			update_env_cd(t_env *e, char **c, int i, int j);

/*
** Fonctions in update_env_2 file
*/

void			display_prompt(t_env *e, long sec);
void			copy_pwd(t_env *e, int i);
void			go_back_cd(t_env *e, int i, int j);

/*
** Fonctions in update_env_3 file
*/

char			*gen_pwd_cd(char *c, char *p, int i, int *k);
void			update_env_cd_2(t_env *e, char *c, int k, int j);

/*
** Fonctions in error_minishell file
*/

void			error_command_not_found(char *c);
void			error_op_dir2(char *c);
void			error_op_dir(t_env *e, int i);
void			error_cl_dir(t_env *e, int i);
void			error_fork(void);

/*
** Fonctions in error_minishell_2 file
*/

void			error_wrong_pwd(char *c);
void			error_chdir_2(char *c);
void			error_chdir(char *c, int i);
void			error_home(void);
void			error_pwd(t_env *e);

/*
** Fonctions in error_minishell_3 file
*/

void			error_oldpwd(t_env *e);
void			error_lstat(char *c);
void			error_op_dir_2(char *c);
void			error_cl_dir_2(char *c);
void			malloc_error(void);

/*
** Fonctions in finish_to_norme_sh file
*/

void			end_complete_av_4(t_env *e, int i, int len);
void			error_cd_perm(char *c);
void			error_cd_no_file(char *c);
void			error_pwd_2(t_env *e);
int				mini_compt_c(char **c);

/*
** Fonctions in finish_to_norme_2 file
*/

char			*ft_env_z(char **c, char *ln, int j);
void			end_update_cd_2(char *c, t_env *e, int *k, int i);
void			control_av_echo_2(char *line, char **c, int i, int k);
void			control_av_echo_3(char *line, char **c, int i, int j);

/*
** Fonctions in split_simple_quote file
*/

char			**sft_split_quote(char **c, int i, int j, int tp);

#endif
