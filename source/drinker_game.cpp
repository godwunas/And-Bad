#include "drinker_game.h"
#include "player_interface.h"
#include "card_deck.h"
#include "ai_player.h"
#include "user_player.h"
#include <algorithm>

namespace drinker{

	drinker_game::drinker_game()
		:players_(players::PLAYER_COUNT) 
		, cur_card_deck_(&(card_deck::getInstance(normal_mode)))
		, playing_table_(&(playing_table::getInstance()){		
		players_[USER_PLAYER].reset(new user_player);
		players_[AI_PLAYER].reset(new ai_player);		
	}

	void drinker_game::start_game(){		
		auto player_in_game = players_.size();

		auto find_active_pl = [](const std::unique_ptr<player_interface>& pl) { return pl->is_active_player(); };

		while (1 < std::count_if(players_.begin(), players_.end(), find_active_pl)){			
			for_each(players_.begin(), players_.end(), [](const std::unique_ptr<player_interface>& pl) { pl->make_move(); });
			std::find_if(players_.begin(), players_.end(), [](const std::unique_ptr<player_interface>& pl){ *pl == *(playing_table_->get_winner()); });
		}
		std::vector<std::unique_ptr<player_interface>>::iterator winner = find_if(players_.begin(), players_.end(), find_active_pl);
	}
}