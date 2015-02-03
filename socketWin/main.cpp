#include <iostream>
#include <string>
#include "socket.h"

using namespace std;

//CInitSock initSock;

bool bSeverBuilt = false;

DWORD WINAPI severThread(LPVOID lpParameter)
{
	string ip = "127.0.0.1";
	SeverSocket s;
	if( s.build( ip, 4000 ) )
	{
		bSeverBuilt = true;
		s.waitClient();
	}
	else
	{
		bSeverBuilt = false;
		return 0;
	}

	return 0;
}

int main()
{
	CInitSock initSock;
	
	//create a thread for the sever socket
	HANDLE SeverThread = CreateThread(NULL, 0, severThread, NULL, 0, NULL );
	if ( SeverThread == NULL )
	{
		cout<<"Create Thread Failed!"<<endl;
	}

	//wait for the sever socket be created
	while( !bSeverBuilt ){}
	
	while( bSeverBuilt )
	{
		string linkIP;
		int linkPort;

		cout<<endl;
		cout<<"exitmain  --quit the program."<<endl;
		cout<<"Input the IP of sever: ";
		cin>>linkIP;
		//linkIP = "127.0.0.1";

		//exit the main thread
		if( linkIP == "exitmain" )
		{
			CloseHandle(SeverThread);
			system("pause");
			return 0;
		}

		cout<<"Input the Port: ";
		cin>>linkPort;
		//linkPort = 4000;

		//Client socket
		ClientSocket c;
		if( c.link( linkIP, linkPort ) )
		{
			bool bDis = true;
			bool bAddBook = true;
			while( bAddBook )
			{
				if( bDis )
				{
					string recvStr;
					c.recvMsg( recvStr );
				
					if( recvStr == "$" )
					{
						bDis = false;
						continue;
					}
					else
						cout<<recvStr;
				}
				else
				{
					string sendStr;
					getline(cin, sendStr);
					if( sendStr == "" )
						continue;

					if( sendStr == "!quit" )
						bAddBook = false;

					c.sendMsg( sendStr );
					bDis = true;
				}
			}
		}

		c.close();
	}


	
	CloseHandle(SeverThread);

	system("pause");
	return 0;
}
