#include "Player.h"

Player::Player()
{
	sprite.content = '@';
	sprite.color.foreground_color = int(Color::Type::Red);
	sprite.color.background_color = 0;
	current_hp = 2;
	max_hp = 3;
	real_max_hp = 3;
}
