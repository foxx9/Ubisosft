#pragma once

#include "NetPeer.h"
#include "NetSocket.h"
#include "GenericRPC.h"
#include "GenericRPCListener.h"
#include "Msg.h"

namespace Shared
{
	//**********************************************************************************************************************
	class NetworkManager
	{
	public:
		NetworkManager(const NetPeer& brokerPeer_in , unsigned short listen_port_in);
		virtual ~NetworkManager();

		bool	Init();
		bool	Refresh();
		bool	Term();

		unsigned short	GetListenPort() const;
		const NetPeer&	GetBroker() const;

		int	Send(const NetPeer& peerTo_in, Msg &msg_in);
		int	SendToBroker(Msg &msg_in);

	protected:

		unsigned short	m_listening_port;
		NetSocket		m_socket;
		NetPeer			m_broker;
	};

} //namespace Shared
