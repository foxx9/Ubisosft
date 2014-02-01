

#include "engine.h"

#include <StringId.h>

// do not touch
int main(void)
{
	Shared::StringId GameId = "MyMarvelousGame";

	Client::Engine::Create();

	Client::Engine* instance = Client::Engine::GetInstance();

	bool ret = instance->Init();

	while(ret = instance->Tick()) {}

	instance->Term();
	Client::Engine::Destroy();

	return 0;
}