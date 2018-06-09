/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mini.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:17 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 19:31:08 by vbranco     ###    #+. /#+    ###.fr     */
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

/*
**	ENV >> ft_initialise.c
*/
t_env			*ft_initialise(void);
t_env			*ft_get_env(char **env);
void			ft_dell(t_env_head **s);
void			ft_add(t_env **s, t_env *add);

/*
**	DEBUG---------------------------------
*/
//------------------------------------------

/*
**	MAIN.c
*/
void			execute(t_env_head *head, char **parsed, int i);

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
void			update_env(t_env_head *head, char *dir);
int				test_env_flags(t_env_head *head, char **parsed);
int				ft_print_env(t_env_head *head);
void			ft_updating_var(t_env_head *head, char *var, char *current);
void			ft_create_var(t_env_head *head, char *var, char *dir);

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
int				test_exe(t_env *env, char **parsed, char **exe);

/*
**	PARSING.c
*/
char			**ft_split(char *line);

/*
**	TOOLS.c
*/
int				searching_on_env(t_env_head *head, char *looking);
int				ft_error(char *error_message, char **parsed, int index);
int				ft_count_args_shell(char **parsed);
void			ft_get_index_flag(char **parsed, int *, int *flag);
void			shell_top(void);


#endif
