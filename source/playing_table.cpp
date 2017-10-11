#include "playing_table.h"

namespace drinker {

	playing_table* playing_table::single_play_table_ = nullptr;
	destroy_play_table playing_table::destroy_play_table_;

	destroy_play_table::~destroy_play_table(){
		if (play_table_ != nullptr)
			delete play_table_;
	}

	void destroy_play_table::instance(playing_table* play_table){
		if (play_table_ != nullptr && play_table != nullptr)
			play_table_ = play_table;
	}

	player_interface* playing_table::get_winner(){
		auto max_card_it = std::max_element(cards_on_hand.begin(), cards_on_hand.end(), [](const card_interface& lhs, const card_interface& rhs) {
			if (lhs.is_tuz() && rhs.is_six() || lhs < rhs)
				return true;
			else
				return false;
		});

		max_card_it->get_owner_player();
	}

	playing_table& playing_table::getInstance() {
		if (single_play_table_ == nullptr){
			single_play_table_ = new playing_table;
			destroy_play_table_.instance(single_play_table_);
		}

		return *single_play_table_;
	}
}