#include "ai_player.h"

namespace drinker{
	void ai_player::make_move() {
		playing_table::getInstance()->to_get_card(to_send_card(0));
	}
}