//**********************************************************************************************************************
#pragma once

#include "NetworkManager.h"

namespace Session
{
	//**********************************************************************************************************************
	class SessionService : public Shared::GenericRPCListener
	{
	public:
		SessionService(Shared::NetworkManager* manager);
		~SessionService();

		// GenericRPCListener interface override
		bool OnIncomingQuery(Shared::IncomingQuery& query);
		bool OnInit();
		bool OnUpdate();
		bool OnTerm();
	};

} //namespace Session
