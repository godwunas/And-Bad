#include "user_player.h"
#include "playing_table.h"
#include <iostream>

namespace drinker{
	void user_player::make_move(){
		std::wcout << "enter eny key to continue";

		wchar_t c;
		std::wcin >> c;

		playing_table::getInstance().to_get_card(to_send_card(0), push_mode::PUSH_BACK);
	}
}