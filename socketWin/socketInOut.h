#ifndef SOCKETINOUT_H
#define SOCKETINOUT_H

#include <Windows.h>
#include <string>
#include <memory.h>

using namespace std;

void sendMsg( const SOCKET &dst, const string &msg );
void recvMsg( const SOCKET &dst, string &msg );
void waitTime( int count );


#endif