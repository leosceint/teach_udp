#include <iostream>
#include <WinSock2.h>

#pragma comment (lib, "Ws2_32.lib")

using namespace std;

int main()
{
	const char* net_ip = "192.168.136.255"; 
	const int port_servers = 27000;
	
    WSADATA WSAData;
    SOCKET connection;
    SOCKADDR_IN addr;
    int sinlen = sizeof(SOCKADDR_IN);
    char broadcast = 'a';

    WSAStartup(MAKEWORD(2, 0), &WSAData);
    connection = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    addr.sin_addr.s_addr = inet_addr(net_ip);
    addr.sin_port = htons(port_servers);
    addr.sin_family = PF_INET;

    int status = bind(connection, reinterpret_cast<sockaddr*>(&addr), sinlen);
    cout << "Bind status -- " << status << endl;

    status = setsockopt(connection, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
    cout << "Setsockopt status -- " << status << endl;

    const char buffer[] = "Hello world!";
    int bufflen = strlen(buffer);
    while(true)
    {
        status = sendto(connection, buffer, bufflen, 0, reinterpret_cast<sockaddr*>(&addr), sinlen);
        cout << "Send message: " <<  buffer << endl;
        
        if(status == SOCKET_ERROR)
            break;
    }
    closesocket(connection);
    WSACleanup();
    cout<<"Socket for connection Closed" << endl;

    return 0;
}