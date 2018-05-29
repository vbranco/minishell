#include "mini.h"

int				ft_error(char *error_message, char **parsed, int index)
{

	ft_putstr_fd(error_message, 2);
	if (parsed != NULL)
		ft_putendl_fd(parsed[index], 2);
	else
		ft_putchar_fd('\n', 2);
	return (1);
}

static	int		ft_count_signes(char *str, char c)
{
	int			i;
	int			a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == c)
			a++;
		if (c == '.' && str[i] == '/' && a >= 0)
			a--;
		i++;
	}
	return (a);
}

static	void	ft_upgrade_dir(char *parsed, char *pwd, char **dir)
{
	char		*tmp;

	tmp = ft_strdup(*dir);
	free(*dir);
	
	free(tmp);
}

static	int		ft_path(char *s)
{
	int			i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/' && s[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

static	char	*ft_new_dir(char *parsed, char *pwd, int nb)
{
	int			len;
	char		*dir;

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
	if (ft_path(parsed))
		ft_upgrade_dir(parsed, pwd, &dir);
	return (dir);
}

char			*get_prev_dir(char **parsed, char *pwd)
{
	char		*dir;
	int			i;
	int			z;
	int			a;

	i = ft_count_signes(parsed[1], '.');
	z = ft_count_signes(pwd, '/');
	dir = NULL;
	if (i >= 7)
		return (NULL);
	i--;
	if (i == 0)
		return (pwd);
	if (i >= z)
		return (ft_strdup("/"));//attention fuite de memoire
	else
		dir = ft_new_dir(parsed[1], pwd, i);
	return (dir);
}
