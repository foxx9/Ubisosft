#pragma once

#include "GenericRPCListener.h"
#include "NetworkManager.h"

namespace Broker
{
	//**********************************************************************************************************************
	class Broker : public Shared::GenericRPCListener
	{
	public:
		Broker(Shared::NetworkManager* manager);
		~Broker();

		// GenericRPCListener interface
		bool OnIncomingQuery(Shared::IncomingQuery& query);
		bool OnInit();
		bool OnUpdate();
		bool OnTerm();
	};

} //namespace Broker
