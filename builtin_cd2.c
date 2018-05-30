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
		if (c == '.' && str[i] == '/' && str[i + 1] == '.')
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

static	int		ft_path(char *s, char **dir)
{
	int			i;
	int			len;
	char		tmp[1096];

	i = 0;
	len = ft_strlen(s);
	ft_bzero(tmp, 1096);
	if (s[len - 1] != '/' && s[len - 1] != '.')
	{
		len--;
		while (len > 0)
		{
			if (s[len] == '/')
			{
				i = len;
				break ;
			}
			len--;
		}
		ft_strcat(tmp, "/");
		ft_strcat(tmp, (s + i + 1));
		*dir = ft_realloc(*dir, tmp);
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
	ft_path(parsed, &dir);
	return (dir);
}

char			*get_prev_dir(char **parsed, char *pwd, int index)
{
	char		*dir;
	int			i;
	int			z;
	int			a;

	i = ft_count_signes(parsed[index], '.');
	z = ft_count_signes(pwd, '/');
	dir = NULL;
	if (i >= 7)
		return (NULL);
	if (i == 1)
		return (pwd);
	i--;
	if (i >= z)
		return (ft_strdup("/"));//attention fuite de memoire
	else
		dir = ft_new_dir(parsed[index], pwd, i);
	return (dir);
}
