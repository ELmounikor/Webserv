
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <unistd.h>
#include <string.h>
#define MAX_EVENTS 20000

void    addEvent(int kq, int fd, int fileter)
{
    struct kevent events[1];
    EV_SET(&events[0], fd, fileter, EV_ADD, 0, 0, NULL);
    if (kevent(kq, events, 1, NULL, 0, NULL) < 0)
    {
        perror("addEvent");
        exit(1);
    }
}

void    DisableEvent(int kq, int fd, int fileter)
{
    struct kevent events[1];
    EV_SET(events, fd, fileter, EV_DISABLE, 0, 0, NULL);
    if (kevent(kq, events, 1, NULL, 0, NULL) < 0)
    {
        perror("DisableEvent");
        exit(1);
    }
}

void    DeleteEvent(int kq, int fd, int fileter)
{
    struct kevent events[1];
    EV_SET(events, fd, fileter, EV_DELETE, 0, 0, NULL);
    if (kevent(kq, events, 1, NULL, 0, NULL) < 0)
    {
        perror("DeleteEvent");
        exit(1);
    }
}

void    EnableEvent(int kq, int fd, int fileter)
{
    struct kevent events[1];
    EV_SET(events, fd, fileter, EV_ENABLE, 0, 0, NULL);
    if (kevent(kq, events, 1, NULL, 0, NULL) < 0)
    {
        perror("EnableEvent");
        exit(1);
    }
}

int main()
{
    const char *response ("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: \
        12\n\nHello world!");
    int socket_server, portno = 8080, client_len, socket_client, kq, new_events;
    int opt = true;
    struct kevent event[MAX_EVENTS];
    struct sockaddr_in serv_addr, client_addr;

    if (((socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0))
    {
        perror("ERROR opening socket");
        exit(1);
    }
    if (setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    memset(serv_addr.sin_zero, 0, sizeof (serv_addr.sin_zero));
    if (bind(socket_server, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind");
        exit(1);
    }
    if (listen(socket_server, SOMAXCONN) < 0)
    {
        perror("listen");
        exit(1);
    }
    client_len = sizeof(serv_addr);
    kq = kqueue();
    addEvent(kq, socket_server, EVFILT_READ);
    while(true)
    {
        new_events = kevent(kq, NULL, 0, event, MAX_EVENTS, NULL);
        if (new_events == -1)
        {
            perror("kevent");
            exit(1);
        }
        for (int i = 0; i < new_events; i++)
        {
            std::cout<<"new event: "<<new_events<<std::endl;
            int event_fd = event[i].ident;
            if (event[i].filter == EVFILT_READ)
            {
                if (event_fd == socket_server)
                {
                    std::cout<<"New connection coming in...\n";    

                    socket_client = accept(event_fd, (struct sockaddr *)&serv_addr, (socklen_t *)&client_len);
                    if (socket_client == -1)
                    {
                        perror("Accept socket error");
                    }
                    addEvent(kq, socket_client, EVFILT_READ);
                    // addEvent(kq, socket_client, EVFILT_WRITE);
                    // DisableEvent(kq, socket_client, EVFILT_WRITE);
                }
                else
                {
                    char buf[1024];
                    size_t bytes_read = recv(event_fd, buf, sizeof(buf), 0);
                    if (bytes_read <= 0)
                    {
                        if (bytes_read < 0)
                            std::cout<<"client read error\n";
                        else if (bytes_read == 0)
                        {
                            DeleteEvent(kq, socket_client, EVFILT_READ);
                            close(event_fd);
                        }
                    }
                    else
                    {
                        //std::cout<<buf<<std::endl;
                        addEvent(kq, socket_client, EVFILT_WRITE);
                        DisableEvent(kq, socket_client, EVFILT_READ);
                        //EnableEvent(kq, socket_client, EVFILT_WRITE);
                    }
                }
            }
            else if (event[i].filter == EVFILT_WRITE)
            {
                std::cout << "Received data from client with ID: " << event_fd << std::endl;
                if (send(event_fd, response, strlen(response), 0) == -1)
                {
                    std::cout<<"client send error\n";
                    close(event_fd);
                }
                DisableEvent(kq, socket_client, EVFILT_WRITE);
                close(event_fd);
            }
        }
    }

    return 0;
}
