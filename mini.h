/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mini.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:17 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/19 17:22:05 by vbranco     ###    #+. /#+    ###.fr     */
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

/*
**	DEBUG---------------------------------
*/
//------------------------------------------

/*
**	BUILTINS.c
*/
int				echo(char **parsed);

/*
**	BUILTIN_CD.c
*/
int				cd(t_env *env, char **parsed);
int				change_dir(t_env *env, char *dir);
char			*get_dir_from_env(t_env *env, char *looking);
int				ft_error(char *error_message, char **parsed, int index);

/*
**	BUILTIN_ENV.c
*/
int				env(t_env *s);
void			update_env(t_env *env, char *pwd);

/*
**	PARSING.c
*/
char			**ft_split(char *line);

#endif
