/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mini.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:17 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/19 19:57:45 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# define CD_TOO_ARGS "cd: too many arguments"
# define CD_NO_FILE "cd: no such file or directory: "
# define CD_BAD_FD "cd: bad file descriptor: "
# define CD_NO_DIR "cd: not a directory: "
# define CD_DENIED "cd: permission denied: "
# define CD_NOT_PWD "cd: string not in pwd: "
# define ENV_VAR "setenv: Variable name must contain alphanumeric characters"
# define UNSETENV_NO_ARG "unsetenv: not enough arguments"
# define NO_CMD ": Command not found"
# define ENV_USAGE "usage: env [-i] [name=value ...] [utility [argument ...]]"

typedef struct		s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}					t_env;

typedef	struct		s_env_head
{
	struct s_env	*next;
}					t_env_head;

typedef	struct		s_pars
{
	char			*get;
	struct s_pars	*next;
}					t_pars;

typedef struct		s_pars_head
{
	struct s_pars	*next;
}					t_pars_head;


/*
**	TOOLS_LST_ENV.c
*/
t_env			*ft_initialise(void);
t_env_head		*ft_initialise_head(void);
void			ft_add(t_env_head *head, t_env *add);
void			ft_dell(t_env_head **s);
void			ft_get_env(t_env_head *head, char **env);

/*
**	TOOLS_LST_PARSE.c
*/
t_pars_head		*ft_initialise_pars_head(void);
void			ft_free_pars(t_pars_head **head);
void			ft_add_pars(t_pars_head *head, char *s);

/*
**	MAIN.c
*/
void			minishell(t_env_head *head);

/*
**	BUILTINS.c
*/
int				echo(t_env_head *head, char **parsed);

/*
**	BUILTIN_CD.c
*/
int				cd(t_env_head *head, char **parsed);

/*
**	BUILTIN_CD2.c
*/

char			*get_prev_dir(char **parsed, char *pwd, int index);
int				ft_count_signes(char *str, char c);

/*
**	BUILTIN_ENV.c
*/
int				environment(t_env_head *head, char **parsed);
int				ft_print_env(t_env_head *head);
void			ft_make_var_info(char *s, char **var_name, char **var_data);

/*
**	BUILTIN_SETENV.c
*/
int				setenvi(t_env_head *head, char **parsed);

/*
**	BUILTIN_UNSETENV.c
*/
int				unsetenvi(t_env_head *head, char **parsed);

/*
**	EXE.c
*/
int				test_exe(t_env *env, char **parsed, int index, char **exe);

/*
**	PARSING.c
*/
char			**ft_parsed(t_env_head *head, char *line);
void			ft_looking_for_special(char *s, int *i);


/*
**	TOOLS.c
*/
char			*searching_on_env(t_env_head *head, char *looking);
int				ft_error(char *error_message, char **parsed, int index);
int				ft_count_args_shell(char **parsed);
void			ft_get_index_flag(char **parsed, int *, int *flag);

/*
**	TOOLS_ENV.c
*/
void			update_env(t_env_head *head, char *dir);
void			ft_updating_var(t_env_head *head, char *var, char *current);
void			ft_create_var(t_env_head *head, char *var, char *data);

/*
**	TOOLS_MINI.c
*/
int				ft_count_nb_env(t_env *lst);
char			**making_env(t_env_head *head, char *exe);
void			ft_print_error_no_exe(char *s);
void			execute(t_env_head *head, char **parsed, int i);
void			execute_2(char *exe, char **parsed, char **env, int i);

/*
**	TOOLS_CD.c
*/
char			*get_dir_from_env(t_env *env, char *looking, char **err_mes);
char			*get_stat(char **parsed, int i, int flag, char *pwd);
int				looking_stat(char *dir);

/*
**	TOOLS_EXE.c
*/
int				exec_in_dir(char **parsed, int index, char **exe);
char			*path_exist(t_env *env);
char			*making_path(char *s1, char *s2, int i);
int				inside_dir(char *path_dir, char *parsed, char **ret);
int				ft_count_p(char *s);

/*
**	TOOLS_PARSING.c
*/
void			ft_create_parse_lst(t_env_head *env, t_pars_head *h, char *s);



/*
**	HEAD_PROMPT.c
*/
void			shell_top(void);
void			print_prompt(t_env_head *head);

#endif
