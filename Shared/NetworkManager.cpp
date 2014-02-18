//********************************************************************************************************************** 
#include "NetworkManager.h" 
#include "Msg.h" 
#include "GenericRPC.h" 
#include "GenericRPCListener.h" 
#include <algorithm>    // std::find 
  
namespace Shared 
{ 
    //********************************************************************************************************************** 
    NetworkManager::NetworkManager(const NetPeer& brokerPeer_in , unsigned short listen_port_in): 
        m_brokerPeer(brokerPeer_in), 
        m_listening_port(listen_port_in) 
    { 
    } 
  
    //********************************************************************************************************************** 
    NetworkManager::~NetworkManager() 
    { 
        m_socket.Close(); 
    } 
  
    //********************************************************************************************************************** 
    unsigned short  NetworkManager::GetListenPort() const
    { 
        return m_listening_port; 
    } 
  
    //********************************************************************************************************************** 
    const NetPeer&  NetworkManager::GetBroker() const
    { 
        return m_brokerPeer; 
    } 
  
    //********************************************************************************************************************** 
    int NetworkManager::Send(const NetPeer& peerTo_in, Msg &msg_in) 
    { 
        return -1; 
    } 
  
    //********************************************************************************************************************** 
    int NetworkManager::SendToBroker(Msg &msg_in) 
    { 
        return -1; 
    } 
  
    //********************************************************************************************************************** 
    bool    NetworkManager::Init() 
    { 
        if (m_socket.Bind(m_listening_port) == false) 
        { 
            return false; 
        } 
  
        return true; 
    } 
  
    //********************************************************************************************************************** 
    bool NetworkManager::AddRPC(GenericRPC& rpc) 
    { 
        RPCListIt it = std::find(m_rpclist.begin(), m_rpclist.end(), &rpc); 
        if (it != m_rpclist.end()) 
        { 
            return false; 
        } 
  
        m_rpclist.push_back(&rpc); 
        return true; 
    } 
  
    //********************************************************************************************************************** 
    bool NetworkManager::RemoveRPC(GenericRPC& rpc) 
    { 
        RPCListIt it = std::find(m_rpclist.begin(), m_rpclist.end(), &rpc); 
        if (it == m_rpclist.end()) 
        { 
            return false; 
        } 
  
        m_rpclist.erase(it); 
  
        return true; 
    } 
  
    //********************************************************************************************************************** 
    bool NetworkManager::AddRPCListener(GenericRPCListener& listener) 
    { 
        RPCListenerListIt it = std::find(m_rpclistenerlist.begin(), m_rpclistenerlist.end(), &listener); 
        if (it != m_rpclistenerlist.end()) 
        { 
            return false; 
        } 
  
        m_rpclistenerlist.push_back(&listener); 
        return true; 
    } 
  
    //********************************************************************************************************************** 
    bool NetworkManager::RemoveRPCListener(GenericRPCListener& listener) 
    { 
        RPCListenerListIt it = std::find(m_rpclistenerlist.begin(), m_rpclistenerlist.end(), &listener); 
        if (it != m_rpclistenerlist.end()) 
        { 
            return false; 
        } 
  
        m_rpclistenerlist.erase(it); 
  
        return true; 
    } 
  
    //********************************************************************************************************************** 
    bool    NetworkManager::Refresh() 
    { 
        NetPeer peerSender; 
        Msg msgData; 
  
        // read socket while incoming data 
        while (m_socket.IsReadable(100)) 
        { 
            if (m_socket.Read(peerSender, msgData) == false) 
            { 
                break; 
            } 
  
            for (RPCListenerListIt it = m_rpclistenerlist.begin(); it != m_rpclistenerlist.end(); ++it) 
            { 
                if ((*it)->OnIncomingData(peerSender, msgData)) 
                { 
                } 
            } 
        } 
  
        // manage RPC 
        for (RPCListIt it = m_rpclist.begin(); it != m_rpclist.end(); ++it) 
        { 
            if ((*it)->OnUpdate()) 
            { 
            } 
        } 
  
        // delete completed rpc 
        /*for (RPCListIt it = m_rpclist.begin(); it != m_rpclist.end(); ++it) 
        { 
            if ((*it)->GetState() == GenericRPC::complete) 
            { 
                m_rpclist.erase(it); 
                continue; 
            } 
        }*/ 
  
        return true; 
    } 
  
    //********************************************************************************************************************** 
    bool    NetworkManager::Term() 
    { 
        m_rpclist.clear(); 
        m_rpclistenerlist.clear(); 
  
        return true; 
    } 
  
  
} // namespace Shared 

/*//**********************************************************************************************************************
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
*/