#ifndef CARD_DECK_H
#define CARD_DECK_H
#include "card_interface.h"
#include <vector>
#include <memory>

enum card_count {
	normal_mode = 36,
	maximize_mode = 54
};

class card_deck_destroy;

//колода карт в виде синглтона
class card_deck{
public:
	static card_deck& card_deck::getInstance(const card_count count_card);

private:
	card_deck(const card_count count);
	~card_deck() {}
	card_deck& operator=(card_deck&& op) = delete;
	card_deck operator=(card_deck& op) = delete;
	card_deck(card_deck& op) = delete;
	card_deck(card_deck&& op) = delete;

	card_count card_count_; //количество карт в колоде
	static card_deck* single_deck; 
	static card_deck_destroy card_deck_destr;
	friend class card_deck_destroy;

	std::vector<card_interface> cards_on_deck;
	void card_mix();
	void card_add();
};

class card_deck_destroy {
private:
	card_deck* single_deck;
public:
	~card_deck_destroy();
	void initialize(card_deck* card_deck_ptr);
};
#endif
