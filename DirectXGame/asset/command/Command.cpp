#include "Command.h"
#include "asset/gameObject/player/Player.h"

//左へ移動を実行
void MoveLeftCommand::Exec(Player& player) { player.MoveLeft(); }

//右へ移動を実行
void MoveRightCommand::Exec(Player& player) { player.MoveRight(); }

//下へ移動を実行
void MoveDownCommand::Exec(Player& player) { player.MoveDown(); }

//上へ移動を実行
void MoveUpCommand::Exec(Player& player) { player.MoveUp(); }

//右へ旋回
void RotateRightCommand::Exec(Player& player) { player.RotateRight(); }

//左へ旋回
void RotateLeftCommand::Exec(Player& player) { player.RotateLeft(); }
