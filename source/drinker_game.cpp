#include "stdafx.h"
#include "drinker_game.h"
#include "player_interface.h"
#include "card_deck.h"
#include "ai_player.h"
#include "user_player.h"

namespace drincker{

	drinker_game::drinker_game()
		:players_(players::PLAYER_COUNT) {
		players_[USER_PLAYER].reset(new user_player);
		players_[AI_PLAYER].reset(new ai_player);
	}

	void drinker_game::start_game(){
		std::vector<std::unique_ptr<player_interface>>::iterator winner = players_.end();
		while (winner == players_.end()){
			winner = std::find_if(players_.begin(), players_.end(), [](const std::unique_ptr<player_interface>& pl){
				pl->make_move();//видимо стол тоже должен быть синглтон и статичный, чтоб обращение к нему (да и к бите) происходило вне игры, а внутри хода игрока 
				return pl->is_dont_have_card();//если карт на руках нет - победитель определен
			});
		}
	}
}