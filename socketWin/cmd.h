#ifndef CMD_H
#define CMD_H

#include <iostream>
#include <limits.h>
#include <memory.h>

#include "PeopleData.h"			//PeopleData class definition
#include "TelBook.h"			//TelBook class definition
#include "socketInOut.h"

using namespace std;


void addEntry( TelBook &book, const SOCKET &client );			//function prototype
void findEntry( TelBook &book, const SOCKET &client );
void deleteEntry( TelBook &book, const SOCKET &client );
void showHelp( TelBook &book, const SOCKET &client );
void displayEntry( TelBook &book, const SOCKET &client );
void deleteAllEntry( TelBook &book, const SOCKET &client );

typedef struct cmd_fun_pair{			//the struct of command and operation pair
   const char* StrCmd;
   void (*CmdFun)( TelBook &book, const SOCKET &client );
}CMD_FUN_PAIR; 

//main function in the sever thread
int main_cmd( const SOCKET &client );



#endif