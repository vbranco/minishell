/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mini.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:17 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/04 19:46:45 by vbranco     ###    #+. /#+    ###.fr     */
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
	struct s_env	*prev;
}					t_env;

/*
**	ENV >> ft_initialise.c
*/
t_env			*ft_initialise(void);
t_env			*ft_get_env(char **env);
void			ft_dell(t_env **s);
void			ft_add(t_env **s, t_env *new);

/*
**	DEBUG---------------------------------
*/
//------------------------------------------

/*
**	BUILTINS.c
*/
int				echo(t_env *env, char **parsed);

/*
**	BUILTIN_CD.c
*/
int				cd(t_env *env, char **parsed);

/*
**	BUILTIN_CD2.c
*/

char			*get_prev_dir(char **parsed, char *pwd, int index);
int				ft_count_signes(char *str, char c);

/*
**	BUILTIN_ENV.c
*/
int				environment(t_env *s);
void			update_env(t_env *env, char *pwd);

/*
**	BUILTIN_SETENV.c
*/
int				setenvi(t_env **env, char **parsed);

/*
**	BUILTIN_UNSETENV.c
*/
int				unsetenvi(t_env **env, char **parsed);

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
int				searching_on_env(t_env *env, char *looking);
int				ft_error(char *error_message, char **parsed, int index);
int				ft_count_args_shell(char **parsed);
void			ft_get_index_flag(char **parsed, int *, int *flag);


#endif
