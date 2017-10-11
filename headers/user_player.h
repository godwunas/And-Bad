#ifndef USER_PLAYER_H
#define USER_PLAYER_H
#include "player_interface.h"

namespace drinker{
	class user_player : public ::player_interface{
	public:
		user_player() = default;
		virtual ~user_player() = default;
	private:
		user_player(const user_player&) = delete;
		user_player& operator =(const user_player&) = delete;
	public:
		void make_move();
	};
}


#endif