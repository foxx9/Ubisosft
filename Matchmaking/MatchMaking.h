//**********************************************************************************************************************
#pragma once

#include "NetworkManager.h"

namespace MatchMaking
{
	//**********************************************************************************************************************
	class MatchMakingService : public Shared::GenericRPCListener
	{
	public:
		MatchMakingService(Shared::NetworkManager* manager);
		~MatchMakingService();

		// GenericRPCListener interface override
		bool OnIncomingQuery(Shared::IncomingQuery& query);
		bool OnInit();
		bool OnUpdate();
		bool OnTerm();
	};

} //namespace MatchMaking
