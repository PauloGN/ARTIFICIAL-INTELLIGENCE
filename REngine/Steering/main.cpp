#include <REngine.h>
#include <AI.h>


namespace
{
	std::unique_ptr<AI::AIWorld> world;

}


void GameInit()
{
	world = std::make_unique<AI::AIWorld>();

}

bool GameUpdate()
{
	

	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;
}

void GameCleanup()
{

}

void RenderDebugUI()
{
}

int main()
{
	REng::Start("Steering");
	GameInit();
	REng::Run(GameUpdate, RenderDebugUI);
	GameCleanup();
	REng::Stop();
	return 0;
}
