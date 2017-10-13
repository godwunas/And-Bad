#include "player_interface.h"

void player_interface::to_get_card(card_interface&& card, push_mode push_pos) {
	card.set_owner_player(this);
	card_holder_interface::to_get_card(std::move(card), push_pos);
}