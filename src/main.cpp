#include "GameEngineImpl/common_types.h"
#include "GameEngineImpl/Scenes/SceneFactory.h"

int main() {
    GameEngineImpl::GameType Game(GameEngineImpl::GameSceneName::MainMenu, &GameEngineImpl::Scenes::NewFactory);
    Game.Run();

    return 0;
}