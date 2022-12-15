#include "GameEngineImpl/common_types.h"
#include "GameEngineImpl/Scenes/SceneFactory.h"
#include "GameEngineImpl/Game.h"

int main() {
    GameEngineImpl::Game Game(GameEngineImpl::GameSceneName::MainMenu, &GameEngineImpl::Scenes::NewFactory);
    Game.Run();

    return 0;
}