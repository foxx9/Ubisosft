#pragma once 
  
#include "NetPeer.h" 
#include "NetSocket.h" 
#include "GenericRPC.h" 
#include "GenericRPCListener.h" 
#include <list> 
  
namespace Shared 
{ 
    class GenericRPC; 
    class Msg; 
  
    //********************************************************************************************************************** 
    class NetworkManager 
    { 
    public: 
        typedef std::list < GenericRPC * >                RPCList; 
        typedef RPCList::iterator                       RPCListIt; 
        typedef std::list < GenericRPCListener *>     RPCListenerList; 
        typedef RPCListenerList::iterator               RPCListenerListIt; 
  
        NetworkManager(const NetPeer& brokerPeer_in , unsigned short listen_port_in); 
        virtual ~NetworkManager(); 
  
        bool    Init(); 
        bool    Refresh(); 
        bool    Term(); 
  
        unsigned short  GetListenPort() const; 
        const NetPeer&  GetBroker() const; 
  
        int Send(const NetPeer& peerTo_in, Msg &msg_in); 
        int SendToBroker(Msg &msg_in); 
  
        bool    AddRPCListener(GenericRPCListener& listener_in); 
        bool    RemoveRPCListener(GenericRPCListener& listener_in); 
  
        bool    AddRPC(GenericRPC& rpc_in); 
        bool    RemoveRPC(GenericRPC& rpc_in); 
  
    protected: 
  
        RPCList             m_rpclist;          // current pending rpcs 
        RPCListenerList     m_rpclistenerlist;  // rpc listeners 
  
        unsigned short  m_listening_port; 
        NetSocket       m_socket; 
        NetPeer         m_brokerPeer; 
    }; 
  
} //namespace Shared 

/*#pragma once

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
*/