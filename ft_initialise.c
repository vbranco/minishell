#include "mini.h"

void	ft_initialise(t_inf *env)
{
	if (!(env = (t_inf*)malloc(sizeof(t_inf))))
		return ;
	env->pwd = NULL;
	env->oldpwd = NULL;
	env->home = NULL;
	env->path = NULL;
}
