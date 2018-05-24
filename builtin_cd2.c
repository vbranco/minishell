#include "mini.h"

int		ft_error(char *error_message, char **parsed, int index)
{

	ft_putstr_fd(error_message, 2);
	if (parsed != NULL)
		ft_putendl_fd(parsed[index], 2);
	else
		ft_putchar_fd('\n', 2);
	return (1);
}

static int	ft_count_signes(char *str, char c)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == c)
			a++;
		i++;
	}
	return (a);
}

static char	*ft_new_dir(char *pwd, int nb)
{
	int		len;
	char	*dir;

	dir = NULL;
	len = ft_strlen(pwd) - 1;
	while (len >= 0)
	{
		if (pwd[len] == '/')
		{
			nb--;
			if (nb == 0)
			{
				dir = ft_strsub(pwd, 0, len);
				break ;
			}
		}
		len--;
	}
	return (dir);
}

char		*get_prev_dir(char **parsed, char *pwd)
{
	char	*dir;
	int		i;
	int		z;

	i = 0;
	z = ft_count_signes(pwd, '/');
	dir = NULL;
	while (parsed[1][i] && parsed[1][i] == '.')
		i++;
	if (i >= 7)
		return (NULL);
	i--;
	if (i == 0)
		return (pwd);
	if (i >= z)
		return (ft_strdup("/"));//attention fuite de memoire
	else
		dir = ft_new_dir(pwd, i);
	return (dir);
}
