//**********************************************************************************************************************
#include "NetSocket.h"

namespace Shared
{
	NetSocket::NetSocket()
	{
		m_socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	}

	NetSocket::~NetSocket()
	{
		Close();
	}

	bool NetSocket::Bind(unsigned short port_in)
	{
		SOCKADDR_IN sin;
		sin.sin_addr.s_addr = 0;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port_in);

		int ret = bind(m_socket,(SOCKADDR*) &sin, sizeof(sin));

		u_long boption = 1;
		int err = ioctlsocket(m_socket,FIONBIO,&boption);
		return ret >= 0;
	}

	bool NetSocket::Close()
	{
		return closesocket(m_socket);
	}

	bool NetSocket::IsReadable(long time_msec_in)
	{
		struct timeval time_val;
		time_val.tv_sec = time_msec_in /1000 ;
		time_val.tv_usec =  time_msec_in - time_val.tv_sec * 1000;
	    fd_set set;
		FD_ZERO(&set);
		FD_SET(m_socket, &set);

		if ( select(m_socket+1, &set, NULL, NULL, &time_val))
		{
			return FD_ISSET(m_socket, &set);
		}
		return false;

	}

	bool NetSocket::IsWritable(long time_msec_in)
	{
		struct timeval time_val;
		time_val.tv_sec = time_msec_in /1000 ;
		time_val.tv_usec =  time_msec_in - time_val.tv_sec * 1000;
		fd_set set;
		FD_ZERO(&set);
		FD_SET(m_socket, &set);

		if ( select(m_socket +1, NULL, &set, NULL, &time_val))
		{
			return FD_ISSET(m_socket, &set);
		}
		return false;
	}

	bool NetSocket::Read(NetPeer &peerFrom_out, Msg& msg_out)
	{
		//if ( IsReadable(2000) )
		{
			SOCKADDR_IN sin;
			int len = sizeof(sin);
			int bytesRead =  recvfrom(m_socket, msg_out.GetBuffer(), msg_out.CAPACITY, 0, (SOCKADDR *) &sin, &len);
			msg_out.SetBufferSize(bytesRead);
			peerFrom_out.SetIPAddress(ntohl(sin.sin_addr.s_addr));
			peerFrom_out.SetPortNumber(ntohs(sin.sin_port));
			//TODO handle peerFrom_out

			return (bytesRead > 0);
		}
	}

	int NetSocket::Send(const NetPeer& peerTo_in, const Msg& msg_in)
	{
		//if ( IsWritable(2000) )
		{
			SOCKADDR_IN sin;
			sin.sin_addr.s_addr = htonl(peerTo_in.GetIPAddress());
			sin.sin_family = AF_INET;
			sin.sin_port = htons(peerTo_in.GetPortNumber());
			int ret = sendto(m_socket,msg_in.GetBuffer(),msg_in.GetBufferSize(),0, (SOCKADDR *) &sin, sizeof(sin));
			return ret;
		}

		return 0;
	}


} //namespace Shared
