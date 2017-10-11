#ifndef PLAYING_TABLE_H
#define PLAYING_TABLE_H
#include "card_holder_interface.h"
#include <vector>
#include <memory>

class player_interface;
class playing_table;
class card_deck;

namespace drinker{
	class destroy_play_table{
	private:
		playing_table* play_table_;
	public:
		void instance(playing_table* play_table);

		destroy_play_table() = default;
		~destroy_play_table();
	};

	class playing_table : public card_holder_interface{
		enum players{//temporary enum
			USER_PLAYER = 0,
			AI_PLAYER,
			PLAYER_COUNT,
		};
	private:
		playing_table();
		~playing_table() = default;
		playing_table(const playing_table&) = delete;
		playing_table& operator =(const playing_table&) = delete;
		playing_table(const playing_table&&) = delete;
		playing_table&& operator =(const playing_table&&) = delete;

		static playing_table* single_play_table_;
		static destroy_play_table destroy_play_table_;
		std::vector<std::unique_ptr<player_interface>> players_;
		card_deck* cur_card_deck_;
		friend class destroy_play_table;
 	public:
		player_interface* get_winner();
		playing_table& getInstance();
		void start_game();
	};
}


#endif