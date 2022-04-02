#include "../includes/client_server.h"

void send_filename(int client_fd, t_client_data *data){
    data->filename_len = itoa(strlen(data->name_to_save_file));
    write(client_fd, data->filename_len, strlen(data->filename_len));
    write(client_fd, " ", 1);
    write(client_fd, data->name_to_save_file, strlen(data->name_to_save_file));
}

char	*strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*new;

	new = NULL;
	if (s1 && s2)
	{
		len = strlen(s1) + strlen(s2);
		new = (char *)malloc(len + 1);
		if (!(new))
			return (NULL);
		while (*s1 != '\0')
		{
			*new = *s1;
			new++;
			s1++;
		}
		while (*s2 != '\0')
			*new++ = *s2++;
		*new = '\0';
		new -= len;
	}
	return (new);
}

static	char	*ft_itoadigit(int n)
{
	char	*str;

	if (n >= 0)
	{
		str = (char *)malloc(2);
		if (str != NULL)
		{
			str[0] = n + '0';
			str[1] = '\0';
		}
	}
	else
	{
		str = (char *)malloc(3);
		if (str != NULL)
		{
			str[0] = '-';
			n = n * -1;
			str[1] = n + '0';
			str[2] = '\0';
		}
	}
	return (str);
}

static	int	char_count(int n)
{
	long	m;
	int		i;

	i = 0;
	m = n;
	if (n < 0)
		m = m * -1;
	while (m != 0)
	{
		m = m / 10;
		i++;
	}
	if (n < 0)
		i++;
	return (i);
}

static void	ft_fill_str(char *str, long first, int i)
{
	while (i >= 0)
	{
		str[i] = (first % 10) + '0';
		first = first / 10;
		i--;
	}
}

char	*itoa(int n)
{
	long	first;
	int		i;
	char	*str;

	i = 0;
	first = n;
	if (n > -10 && n < 10)
	{
		str = ft_itoadigit(n);
		return (str);
	}
	i = char_count(n);
	str = (char *)malloc(i + 1);
	if (str != NULL)
	{
		str[i] = '\0';
		i--;
		if (n < 0)
			first = first * -1;
		ft_fill_str(str, first, i);
		if (n < 0)
			str[0] = '-';
	}
	return (str);
}

int64_t get_filesize(int file_fd){
    struct stat _fileStatbuff;
    fstat(file_fd, &_fileStatbuff);
    // int64_t _file_size = 0;
    return(_fileStatbuff.st_size); 
}

char	*strnew(size_t len)
{
	size_t	n;
	char	*newstr;

	n = 0;
	newstr = malloc(len + 1);
	if (!(newstr))
		return (NULL);
	while (n <= len)
	{
		newstr[n] = '\0';
		n++;
	}
	return (newstr);
}