#include "socket.h"

using namespace std;

bool ClientSocket::createClientSocket()
{
	Socket = socket(get_m_domain(), get_m_type(), get_m_protocol());
	if ( Socket == INVALID_SOCKET )
	{
		cout<<"Create Socket Failed!!"<<endl;
		return false;
	}
	else
		return true;
}

bool ClientSocket::link( string &ip_address, int port )
{
	//assert( regex_match( ip_address, ip_pattern ) && 1 <= port && port <= 65535 );

	sever_IP_ADDRESS = ip_address;
	sever_PORT = port;

	if( !createClientSocket() )
		return false;

	sever_addr.sin_family = get_m_domain();
	sever_addr.sin_addr.s_addr = inet_addr(sever_IP_ADDRESS.c_str());
	sever_addr.sin_port = htons(sever_PORT);
	memset(sever_addr.sin_zero, 0x00, 8);

    if ( connect(Socket,(sockaddr*)&sever_addr, sizeof(sever_addr)) == SOCKET_ERROR )
    {
		cout<<"Connect Error!!"<<endl;
		return false;
    }
	else
	{
		cout<<"Client: Successfully Connected!"<<endl;
		return true;
	}
}

bool ClientSocket::sendMsg( const string &msg )
{
	int bFlag;
	const char *buffer = msg.c_str();

	bFlag = send(Socket, buffer, (int)strlen(buffer), 0);
	if ( bFlag == SOCKET_ERROR )
	{
		cout<<"Client Send Infomation Error!"<<endl;
		return false;
	}
	else
		return true;
}

bool ClientSocket::recvMsg( string &msg )
{
	int bFlag;
	char buffer[MAX_PATH];

	bFlag = recv( Socket, buffer, sizeof(buffer), 0 ); 
	if( bFlag == SOCKET_ERROR )
	{
		cout<<"Client Receive Information Error!"<<endl;
		return false;
	}
	else
	{
		msg = buffer;
		return true;
	}
}

void ClientSocket::close()
{
	this->~ClientSocket();
}

bool SeverSocket::createSeverSocket()
{
	Socket = socket(get_m_domain(), get_m_type(), get_m_protocol());
	if ( Socket == INVALID_SOCKET )
	{
		cout<<"Create Socket Failed!!"<<endl;
		return false;
	}
	else
		return true;
}

bool SeverSocket::build( string &ip_address, int port )
{
	//assert( regex_match( ip_address, ip_pattern ) && 1 <= port && port <= 65535 );

	local_IP_ADDRESS = ip_address;
	local_PORT = port;

	if( !createSeverSocket() )
		return false;

	local_addr.sin_family = get_m_domain();
	local_addr.sin_addr.s_addr = inet_addr(local_IP_ADDRESS.c_str());
	local_addr.sin_port = htons(local_PORT);
	memset(local_addr.sin_zero, 0x00, 8);

    if ( bind(Socket, (sockaddr*)&local_addr, sizeof(local_addr)) == SOCKET_ERROR )
    {
		cout<<"Bind Error!!"<<endl;
		return false;
    }
	
	if ( listen(Socket, c_backlog) == SOCKET_ERROR )
	{
		cout<<"Listen Failed!!"<<endl;
		return false;
	}

	cout<<"Sever ip: "<<inet_ntoa(local_addr.sin_addr)<<endl;
	cout<<"port: "<<ntohs(local_addr.sin_port)<<endl;
	cout<<"Severice started......"<<endl;

	return true;
}

bool SeverSocket::waitClient()
{
	while ( true )
	{
		client_addrLen = sizeof(client_addr);
		client_Socket = accept(Socket, (struct sockaddr*)&client_addrLen, &client_addrLen);
		if ( client_Socket == INVALID_SOCKET )
		{
			cout<<"Accept Failed!!"<<endl;
			return false;
		}

		cout<<"Sever: Successfully Connected!!"<<endl;

		main_cmd( client_Socket );
	}

	return true;
}

void SeverSocket::close()
{
	this->~SeverSocket();
}



