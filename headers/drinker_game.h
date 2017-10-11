#ifndef DRINKER_GAME_H
#define DRINKER_GAME_H
#include <vector>

class player_interface;
class card_deck;
class playing_table;

namespace drinker{
	class drinker_game{
		enum players{
			USER_PLAYER = 0,
			AI_PLAYER,
			PLAYER_COUNT,
		};

	public:
		drinker_game();
		~drinker_game() = default;

	private:
		drinker_game(const drinker_game&) = delete;
		drinker_game& operator=(const drinker_game&) = delete;

	public:
		void start_game();

	private:
		std::vector<std::shared_ptr<player_interface>> players_;
		card_deck* cur_card_deck_;//не уверен что надо делать указатель, но так можно из заголовка вынести реализацию же...
		playing_table* playing_table_;
	};
}

#endif