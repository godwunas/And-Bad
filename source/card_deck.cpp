#include "card_deck.h"

card_deck* card_deck::single_deck = nullptr;
card_deck_destroy card_deck::card_deck_destr;

card_deck_destroy::~card_deck_destroy()
{
	if (single_deck != nullptr)
		delete single_deck;
}

card_deck::card_deck(const card_count count) : card_count_(count) {
	cards_on_deck.reserve(static_cast<size_t>(card_count_));
}

void card_deck_destroy::initialize(card_deck* card_deck_ptr)
{
	if (card_deck_ptr != nullptr)
		single_deck = card_deck_ptr;
}

card_deck& card_deck::getInstance(const card_count count_card){
	if (single_deck == nullptr){
		single_deck = new card_deck(count_card);
		card_deck_destr.initialize(single_deck);
	}

	return *single_deck;
}

void card_deck::card_add(){
}

void card_deck::card_mix() {

}