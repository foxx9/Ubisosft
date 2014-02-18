//**********************************************************************************************************************
#include "NetPeer.h"
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <iostream>

namespace Shared
{
	NetPeer::NetPeer()
	{
		m_IpAddress = -1;
		m_PortNumber = -1;
	}

	NetPeer & NetPeer::operator=(const NetPeer& other)
	{
		m_IpAddress = other.m_IpAddress;
		m_PortNumber = other.m_PortNumber;
		return *this;
	}

	NetPeer::NetPeer(const NetPeer &other)
	{
		m_IpAddress = other.m_IpAddress;
		m_PortNumber = other.m_PortNumber;
	}

	NetPeer::NetPeer(unsigned int  ip_in, unsigned short port_in)
	{
		m_IpAddress = (ip_in);
		m_PortNumber = (port_in);
	}

	NetPeer::NetPeer(const char* hostname_in,  unsigned short port_in)
	{
		m_IpAddress = ntohl(inet_addr(hostname_in));
		m_PortNumber = (port_in);
	}

	bool NetPeer::operator==(NetPeer const& other)
	{
		return m_IpAddress == other.m_IpAddress && m_PortNumber == other.m_PortNumber;
	}

	bool NetPeer::IsValid() const
	{
		return m_IpAddress != -1 && m_PortNumber != -1 ;
	}

	unsigned int NetPeer::GetIPAddress() const
	{
		return (m_IpAddress);
	}

	unsigned short NetPeer::GetPortNumber() const
	{
		return (m_PortNumber);
	}

	void NetPeer::SetIPAddress(unsigned int ipaddress)
	{
		m_IpAddress = (ipaddress);
	}

	void NetPeer::SetPortNumber(unsigned short port)
	{
		m_PortNumber = (port);
	}

} //namespace Shared
