#include "utils.h"

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

int socket_with_error_handler(int domain, int type, int protocol){
    int res = 0;
    res = socket(domain, type, protocol);
    if (res == -1){
        perror("Error: ");
        exit(EXIT_FAILURE);
    }
    return res;
}

void bind_with_error_handler(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int res = 0;
    res = bind(sockfd, addr, addrlen);
    if (res == -1){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *adr, socklen_t *addrlen){
    int res = accept(sockfd, adr, addrlen);
    if(res == -1){
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void listen_with_error_handler(int sockfd, int backlog){
    int res = listen(sockfd, backlog);
    if (res == -1){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
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