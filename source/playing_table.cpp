#include "playing_table.h"
#include "user_player.h"
#include "ai_player.h"
#include "card_deck.h"

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

	
	playing_table::playing_table()
		:players_(players::PLAYER_COUNT)
		, cur_card_deck_(&(card_deck::getInstance(normal_mode))){
		players_[USER_PLAYER].reset(new user_player);
		players_[AI_PLAYER].reset(new ai_player);
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

	void playing_table::start_game(){
		auto player_in_game = players_.size();
		player_interface* last_active_pl = nullptr;

		while (1 < player_in_game){
			for_each(players_.begin(), players_.end(), [](const std::unique_ptr<player_interface>& pl) { pl->make_move(); });
			last_active_pl = get_winner();
			std::for_each(cards_on_hand.begin(), cards_on_hand.end(), [&last_active_pl](card_interface& card) { last_active_pl->to_get_card(std::move(card), push_mode::PUSH_BACK); });
			cards_on_hand.clear();
		}
	}
}