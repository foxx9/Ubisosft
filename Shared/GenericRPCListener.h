#pragma once

#include "NetPeer.h"
#include "Msg.h"

namespace Shared
{
	//**********************************************************************************************************************
	class IncomingQuery
	{
	public:
		IncomingQuery();
		NetPeer& GetFrom();

		bool Reply(Msg &content_in);

	protected:
		NetPeer 			m_peerFrom;

	};

	//**********************************************************************************************************************
	class GenericRPCListener
	{
	public:
		virtual bool OnIncomingQuery(Shared::IncomingQuery& query);
		virtual bool OnInit();
		virtual bool OnUpdate();
		virtual bool OnTerm();
	};

} //namespace Shared