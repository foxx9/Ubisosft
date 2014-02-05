//**********************************************************************************************************************
#pragma once

namespace Shared
{
	//**********************************************************************************************************************
	class NetPeer
	{
	public:
		NetPeer();
		NetPeer(unsigned int  ip_in, unsigned short port_in);
		NetPeer(const char* hostname_in,  unsigned short port_in);
		NetPeer(const NetPeer &other);

		unsigned int		GetIPAddress() const;
		unsigned short		GetPortNumber() const;
		void				SetIPAddress(unsigned int ipaddress);
		void				SetPortNumber(unsigned short port);

		bool				IsValid() const;

		NetPeer &			operator=(const NetPeer& other);
		bool				operator==(const NetPeer& other);

	private:
		unsigned int		m_IpAddress;
		unsigned short		m_PortNumber;
	};

} //namespace Shared
