#include "ai_player.h"
#include "playing_table.h"

namespace drinker{
	void ai_player::make_move() {
		playing_table::getInstance().to_get_card(to_send_card(0), push_mode::PUSH_BACK);
	}

	void ai_player::init_name() {
		static char name_gen = 'a';
		name_ = name_gen++;
	}
}