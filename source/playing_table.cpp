#include "playing_table.h"
#include "user_player.h"
#include "ai_player.h"
#include "card_deck.h"
#include "card_interface.h"
#include <algorithm>

namespace drinker {

	playing_table* playing_table::single_play_table_ = nullptr;
	destroy_play_table playing_table::destroy_play_table_;

	destroy_play_table::~destroy_play_table(){
		if (play_table_ != nullptr)
			delete play_table_;
	}

	void destroy_play_table::instance(playing_table* play_table){
		if (play_table_ == nullptr && play_table != nullptr)
			play_table_ = play_table;
	}

	
	playing_table::playing_table()
		:players_(players::PLAYER_COUNT){
		players_[USER_PLAYER].reset(new user_player);
		players_[AI_PLAYER].reset(new ai_player);
	}

	player_interface* playing_table::get_winner(){
		//найдем карту-победительницу(максимальной величины
		auto max_card_it = std::max_element(cards_on_hand_.begin() + inactve_cards_count_, cards_on_hand_.end(), [](const card_interface& lhs, const card_interface& rhs) {
			if (lhs.is_tuz() && rhs.is_six() || is_less_pos(lhs, rhs))
				return true;
			else
				return false;
		});

		//если карт одной величины несколько, ход надо будет позже повторить
		if (std::count_if(cards_on_hand_.begin() + inactve_cards_count_, cards_on_hand_.end(), [&max_card_it](const card_interface& card) {
			return is_equal_pos(*max_card_it, card);
		}) > 1) {
			inactve_cards_count_ = cards_on_hand_.size();
			return nullptr;
		}
		else
			return max_card_it->get_owner_player();
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
		last_active_pl_ = nullptr;

		//перетасуем колоду
		card_deck::getInstance().reset();
		//раздадим карты игрокам за столом
		give_out_cards();

		//игра идет до выявления одного победителя
		while (1 < player_in_game){
			inactve_cards_count_ = 0;
			do{
				//каждый игрок делает ход перед сравнением карт
				for_each(players_.begin(), players_.end(), [](const std::unique_ptr<player_interface>& pl) { pl->make_move(); });
				last_active_pl_ = get_winner();
			} while (last_active_pl_ != nullptr);

			//передать все карты со стола игроку-победителю хода
			move_all_cards_to(last_active_pl_, push_mode::PUSH_BACK);
		}

		//заберем карты игрока победителя и сдадим в биту
		last_active_pl_->move_all_cards_to(&(card_deck::GetHeapOutCard()), push_mode::PUSH_BACK);
	}

	void playing_table::give_out_cards(){
		while (!card_deck::getInstance().is_dont_have_card()){
			std::for_each(players_.begin(), players_.end(), [](const std::unique_ptr<player_interface>& pl){
				pl->to_get_card(card_deck::getInstance().to_send_card(0), push_mode::PUSH_BACK);
			});
		}
	}
}