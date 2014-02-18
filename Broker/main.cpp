//**********************************************************************************************************************
#include "Broker.h"
#include <stdio.h>
int main(void)
{
	WSADATA data;
	WSAStartup(MAKEWORD(1,1),&data);


	Shared::NetPeer myself("127.0.0.1", 8889);
	Shared::NetworkManager netManager(myself, 8889);
	bool is_ok = netManager.Init();
	while (1)
	{
		bool bnewmessage = netManager.Refresh();
		if (bnewmessage)
			printf("new message ...\n");
	}

	return 0;
}