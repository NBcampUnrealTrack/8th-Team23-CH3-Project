#include "T23GameMode.h"
#include "T23Character.h"
#include "T23PlayerController.h"

AT23GameMode::AT23GameMode()
{
	DefaultPawnClass = AT23Character::StaticClass();
	PlayerControllerClass = AT23PlayerController::StaticClass();
}

