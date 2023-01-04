#include <REngine.h>

void GameStart()
{

}

bool GameUpdate()
{
	bool exit = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return exit;
}

//Cleanup
void GameStop()
{

}

void GameUIRender()
{
	ImGui::Begin("Hello World");
	ImGui::End();
}

int main()
{
	REng::Start("MyWindow", 1600, 900);
	REng::Run(GameUpdate, GameUIRender);
	REng::Stop();
}