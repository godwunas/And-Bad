#include "playing_table.h"

namespace drinker {
	void playing_table::get_winner(){
		auto max_card_it = std::max_element(cards_on_hand.begin(), cards_on_hand.end(), [](const card_interface& lhs, const card_interface& rhs) {
			if (lhs.is_tuz() && rhs.is_six() || lhs < rhs)
				return true;
			else
				return false;
		});

		max_card_it->get_owner_player();
	}
}