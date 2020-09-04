#include <iostream>
#include <WinSock2.h>

#include "CanData.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

static unsigned int expectedID = 0x0101;

int executeOnMessageReceived(CanData DataPacket)
{
    unsigned int result = 0;
    if (DataPacket.type == expectedID)
    {
        result = expectedID - 0x0100;
        expectedID++;
    }
    else if(DataPacket.type == expectedID-1)
        return result;
    else
    {
        expectedID = 0x0101;
        result = expectedID - 0x0100;
    }
    if(expectedID > 0x0104)
    {   result = --expectedID - 0x0100;
        expectedID = 0x0101;
    }
    return result;
}

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

    //const int BufferSize = sizeof(CanData);
    //CanData packet;
    const int BufferSize = sizeof(CanFrame);
    CanFrame frame;

    while(true)
    {   
        cout << "Waiting for data" << endl;

        int recv_len;

        //if((recv_len = recvfrom(connection, (char*)&packet, BufferSize, 0, reinterpret_cast<sockaddr*>(&addr), &sinlen) == SOCKET_ERROR))
        if((recv_len = recvfrom(connection, (char*)&frame, BufferSize, 0, reinterpret_cast<sockaddr*>(&addr), &sinlen) == SOCKET_ERROR))
        {
            cout << "WE cannot receive data" << endl;
            break;
        }
        cout << "<WE GET FRAME>" << endl;
        cout << frame << endl;
        cout << "==============" << endl;

        /*if(packet.type == 0x0101 || packet.type == 0x0102 || packet.type == 0x0103 || packet.type == 0x0104)
            cout << "--> WE get : " << packet << endl; 
        if(executeOnMessageReceived(packet) == 4)
            cout << " === WE get data structure of 4 packets ===" << endl << endl;*/
    }

    closesocket(connection);
    WSACleanup();

    return 0;
}