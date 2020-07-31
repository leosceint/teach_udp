#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    const char* ip_server = "0.0.0.0";
    const int port_server = 27000;

    WSADATA WSAData;
    SOCKET connection;
    SOCKADDR_IN addr;
    int sinlen = sizeof(SOCKADDR_IN);

    WSAStartup(MAKEWORD(2, 0), &WSAData); 
    connection = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_server);
    addr.sin_port = htons(port_server);

    if(bind(connection, reinterpret_cast<sockaddr*>(&addr), sinlen) == SOCKET_ERROR)
    {
        cout << "Socket bind failed" << endl;
        exit(1);
    }

    const int BufferSize = 1024;
    char* buffer = new char[BufferSize];

    while(true)
    {   
        cout << "Waiting for data" << endl;

        int recv_len;
        memset(buffer, 0, BufferSize);

        if((recv_len = recvfrom(connection, buffer, BufferSize, 0, reinterpret_cast<sockaddr*>(&addr), &sinlen) == SOCKET_ERROR))
        {
            cout << "WE cannot receive data" << endl;
            break;
        }
        cout << "--> WE get: " << buffer << endl; 

    }

    closesocket(connection);
    WSACleanup();

    return 0;
}