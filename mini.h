#ifndef MINI_H
# define MINI_H

#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

typedef struct	s_inf
{
	char		*pwd;
	char		*oldpwd;
	char		*home;
	char		*path;
}				t_inf;

void			ft_initialise(t_inf *env);

#endif
