#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <Windows.h>
#include <assert.h>
//#include <regex> 

#include "cmd.h"

#pragma comment(lib, "WS2_32")    

using namespace std;

//ip address pattern
//const regex ip_pattern("([1-9]|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])(\\.(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])){3}");
    
class CInitSock        
{   
public:   
    CInitSock(BYTE minorVer = 2, BYTE majorVer = 2)   
    {   
        //initialize WS2_32.dll   
        WSADATA wsaData;   
        WORD sockVersion = MAKEWORD(minorVer, majorVer);   
        if( WSAStartup(sockVersion, &wsaData) != 0 )   
        {   
            exit(0);   
        }   
    }   
    ~CInitSock()   
    {      
        WSACleanup();    
    }   
};   


class SSocket
{
private:
	int m_domain;			//AF_INET、AF_INET6、AF_LOCAL
	int m_type;				//SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET
	int m_protocol;			//IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC

public:
	SSocket( int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP )
		: m_domain(domain), m_type(type), m_protocol(protocol) {};

	int get_m_domain() const { return m_domain; };
	void set_m_domain( const int &domain ) { m_domain = domain; }

	int get_m_type() const { return m_type; };
	void set_m_type( const int &type ) { m_type = type; };

	int get_m_protocol() const { return m_protocol; };
	void set_m_protocol( const int &protocol ) { m_protocol = protocol; };

};

class SeverSocket: public SSocket
{
private:
	int c_backlog;

	//local socket
	SOCKET Socket;
	sockaddr_in local_addr;		//ipv4 address struct
	string local_IP_ADDRESS;	//ip address
	int local_PORT;			    //port

	//client socket
	SOCKET client_Socket;
	sockaddr_in client_addr;
	int client_addrLen;

	//handle of the thread
	HANDLE hThread;

	//create socket
	bool createSeverSocket();

public:
	
	//constructor
	SeverSocket( int backlog = 1, int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP ):	
	SSocket(domain, type, protocol), c_backlog(backlog){ };

	//destructor
	~SeverSocket() { closesocket(Socket); };

	bool build( string &ip_address, int port );
	bool waitClient();
	void close();
};

//client socket class
class ClientSocket: public SSocket
{
private:
	//sever address
	sockaddr_in sever_addr;
	string sever_IP_ADDRESS;
	int sever_PORT;

	SOCKET Socket;

	//create socket
	bool createClientSocket();
	
public:
	//constructor
	ClientSocket( int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP ):	
	SSocket(domain, type, protocol){};

	//destructor 
	~ClientSocket() { closesocket(Socket); };

	bool link( string &ip_address, int port );
	bool sendMsg( const string &msg );
	bool recvMsg( string &msg );
	void close();
};





#endif