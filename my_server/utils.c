#include "utils.h"

// char	*strjoin(char const *s1, char const *s2)
// {
// 	size_t	len;
// 	char	*new;

// 	new = NULL;
// 	if (s1 && s2)
// 	{
// 		len = strlen(s1) + strlen(s2);
// 		new = (char *)malloc(len + 1);
// 		if (!(new))
// 			return (NULL);
// 		while (*s1 != '\0')
// 		{
// 			*new = *s1;
// 			new++;
// 			s1++;
// 		}
// 		while (*s2 != '\0')
// 			*new++ = *s2++;
// 		*new = '\0';
// 		new -= len;
// 	}
// 	return (new);
// }

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