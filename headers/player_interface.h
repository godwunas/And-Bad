#ifndef PLAYER_INTERFACE_H
#define PLAYER_INTERFACE_H
#include "card_interface.h"
#include <vector>
#include <algorithm>

class player_interface{

public:
	player_interface() : cards_on_hand(0) {}
	virtual ~player_interface() {}
private:
	player_interface(const player_interface&);
	player_interface& operator=(const player_interface&);

public:
	void to_get_card(card_interface&& card) { cards_on_hand.push_back(std::move(card)); }
	card_interface&& to_send_card(const int& idx) {
		card_interface temp(std::move(cards_on_hand[idx]));
		cards_on_hand.erase(cards_on_hand.begin(), std::remove(cards_on_hand.begin(), cards_on_hand.end(), temp));
		return std::move(temp);
	}
private :
	std::vector<card_interface> cards_on_hand;
};

#endif