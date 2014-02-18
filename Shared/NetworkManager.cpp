//**********************************************************************************************************************
#include "NetworkManager.h"
#include <iostream>

namespace Shared
{
	NetworkManager::NetworkManager(const NetPeer& brokerPeer_in , unsigned short listen_port_in)
	{
		m_broker = brokerPeer_in;
		m_listening_port = listen_port_in;
	}

	NetworkManager::~NetworkManager()
	{
	}

	unsigned short NetworkManager::GetListenPort() const
	{
		return m_listening_port;
	}

	const NetPeer& NetworkManager::GetBroker() const
	{
		return m_broker;
	}

	bool NetworkManager::Init()
	{
		return m_socket.Bind(m_listening_port);
	}

	bool NetworkManager::Refresh()
	{
		NetPeer peerOut;
		Msg msgOut;

		if (m_socket.Read(peerOut, msgOut))
		{
			std::cout << msgOut.GetBuffer() << std::endl;
			return true;
		}

		return false;
	}

	bool NetworkManager::Term()
	{
		return m_socket.Close();
	}

	int	NetworkManager::Send(const NetPeer& peerTo_in, Msg &msg_in) 
	{
		int err = m_socket.Send(peerTo_in, msg_in);
		return err;
	}

	int NetworkManager::SendToBroker(Msg &msg_in)
	{
		return m_socket.Send(m_broker, msg_in);
	}
} // namespace Shared
