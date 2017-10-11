#ifndef AI_PLAYER_H
#define AI_PLAYER_H
#include "player_interface.h"

namespace drinker{
	class ai_player : public ::player_interface{
	public:
		ai_player() = default;
		virtual ~ai_player() = default;
	private:
		ai_player(const ai_player&) = delete;
		ai_player& operator =(const ai_player&) = delete;
	public:
		void make_move() override;
	};
}


#endif