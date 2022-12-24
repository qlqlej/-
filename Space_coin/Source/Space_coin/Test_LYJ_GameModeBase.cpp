#include "Test_LYJ_GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "player_controller_ui.h"

ATest_LYJ_GameModeBase::ATest_LYJ_GameModeBase() 
{
	PlayerControllerClass = Aplayer_controller_ui::StaticClass();
}
