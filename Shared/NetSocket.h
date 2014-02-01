#pragma once

#include <WinSock.h>

#include "NetPeer.h"
#include "Msg.h"

namespace Shared
{
	//**********************************************************************************************************************
	class NetSocket
	{
	public:

		static const int MTU = 1300 ;

		NetSocket();
		~NetSocket();

		bool	Bind(unsigned short port_in);
		bool	Close();
		bool	IsReadable(long time_msec_in);
		bool	IsWritable(long time_msec_in);

		bool	Read(NetPeer &peerFrom_out, Msg& msg_out);
		bool	Send(const NetPeer& peerTo_in, const Msg& msg_in);

	protected:
		int		_SendTo (unsigned int ip_addr_in, unsigned short port_in,const char* buffer_in, size_t buffer_size_in);

	protected:
		SOCKET	m_socket;

	protected:

	};

} //namespace Shared
