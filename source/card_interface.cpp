#include "card_interface.h"

card_interface::card_interface()
:card_num_(0)
, card_suit_(0)
, owner_player_(nullptr)
{}

card_interface::card_interface(uint16_t&& card_num, uint16_t&& card_suit)
:card_num_(card_num)
, card_suit_(card_suit)
, owner_player_(nullptr)
{}

card_interface::card_interface(card_interface&& other) {
	card_num_ = other.card_num_;
	other.card_num_ = 0;

	card_suit_ = other.card_suit_;
	other.card_suit_ = 0;
}

card_interface& card_interface::operator=(card_interface&& other) {
	if (this != &other) {
		card_num_ = other.card_num_;
		other.card_num_ = 0;

		card_suit_ = other.card_suit_;
		other.card_suit_ = 0;
	}

	return *this;
}

void card_interface::set_owner_player(player_interface* pl) {
	owner_player_ = pl;
}

player_interface* card_interface::get_owner_player() const {
	if (owner_player_ == nullptr)
		throw do_not_have_player_owner(this);
	return owner_player_;
}