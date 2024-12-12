#include "Command.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/player/Player.h"

//左に進む
void KeyboardLeft::Exec(Player* player) { player->MoveLeftKeyboard(); }

//右に進む
void KeyboardRight::Exec(Player* player) {
	player->MoveRightKeyboard();
}

//前に進む
void KeyboardFront::Exec(Player* player) { player->MoveFrontKeyboard(); }

//後ろに進む
void KeyboardBack::Exec(Player* player) { player->MoveBackKeyboard(); }

//水平移動を止める
void KeyboardStopHorizontal::Exec(Player* player) { player->StopHorizontal(); }

//垂直移動を止める
void KeyboardStopVertical::Exec(Player* player) { player->StopVertical(); }
