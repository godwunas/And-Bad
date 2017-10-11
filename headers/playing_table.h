#ifndef PLAYING_TABLE_H
#define PLAYING_TABLE_H
#include "card_holder_interface.h"

class player_interface;


namespace drinker{
	class playing_table : public card_holder_interface{
	public:
		playing_table() = default;
		virtual ~playing_table() = default;
	private:
		playing_table(const playing_table&) = delete;
		playing_table& operator =(const playing_table&) = delete;
	public:
		player_interface* get_winner();
	};
}


#endif