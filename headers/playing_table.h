#ifndef PLAYING_TABLE_H
#define PLAYING_TABLE_H
#include "card_holder_interface.h"
#include <vector>
#include <memory>

class card_deck;
class player_interface;

namespace drinker{
	class playing_table;

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
		player_interface* last_active_pl_;
		int inactve_cards_count_;//карты со стола, не учавствующие в сравнении

		friend class destroy_play_table;
 	public:
		//узнать победителя хода
		player_interface* get_winner();
		static playing_table& getInstance();
		void start_game();
		//метод раздачи карт игрокам
		void give_out_cards();
	};
}


#endif