//**********************************************************************************************************************
#pragma once

#include "NetPeer.h"
#include "Msg.h"

namespace Shared
{
	class NetworkManager;


	//**********************************************************************************************************************
	class GenericRPC
	{
	public:

		enum State
		{
			none,				// initial state
			inprogress_resolve,	// resolving service to broker
			inprogress,			// calling function to server
			complete			// end of RPC
		};

		enum Result
		{
			failed,				// RPC has failed
			success				// RPC has succeed
		};

		enum Error
		{
			ok,
			errorSend,			// error occurs during send message
			errorTimedOut,		// message has timed out
		};

		GenericRPC(NetworkManager& manager_in);
		virtual ~GenericRPC();

		// getter
		State 	GetState() const;
		Result	GetResult() const;
		Error	GetError() const;

		// invoke RPC
		bool	Invoke(const char* servicename_in);
		bool	Invoke(const NetPeer& peerTo_in);

		// NetworkManager life call
		virtual bool OnInit();
		virtual bool OnUpdate();
		virtual bool OnTerm();
		
		// specified RPC to implement
		virtual bool OnIncomingAnswer(const NetPeer& peerFrom_in, const Msg& answer_in) = 0;

	protected:

		State			m_eState;
		Result			m_eResult;
		Error			m_eError;
		Shared::Msg		m_Query;
		Shared::Msg		m_Answer;

		NetPeer			m_dstPeer;

		unsigned int	m_uMaxRetries;
		unsigned int	m_uNbRetries;
		unsigned int	m_tRetryInterval;
		unsigned int	m_tStartTime;
		unsigned int	m_tLastSend;

	};

} //namespace Shared
