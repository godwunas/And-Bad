#include "ai_player.h"
#include "playing_table.h"

namespace drinker{
	void ai_player::make_move() {
		playing_table::getInstance().to_get_card(to_send_card(0), push_mode::PUSH_BACK);
	}
}