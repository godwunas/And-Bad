#ifndef CARD_DECK_H
#define CARD_DECK_H
#include "card_interface.h"
#include <vector>
#include <memory>

enum card_count {
	normal_mode = 36,
	maximize_mode = 54
};

using card = card_interface::card_nums;
using suits = card_interface::suits;

uint16_t card_36[normal_mode] = {card::six|suits::trefles, card::six | suits::piques, card::six|suits::ceurs, card::six|suits::carreaux,
								 card::seven | suits::trefles, card::seven | suits::piques, card::seven | suits::ceurs, card::seven | suits::carreaux,
								 card::eigth | suits::trefles, card::eigth | suits::piques, card::eigth | suits::ceurs, card::eigth | suits::carreaux,
								 card::nine | suits::trefles, card::nine | suits::piques, card::nine | suits::ceurs, card::nine | suits::carreaux,
								 card::ten | suits::trefles, card::ten | suits::piques, card::ten | suits::ceurs, card::ten | suits::carreaux,
								 card::valet | suits::trefles, card::valet | suits::piques, card::valet | suits::ceurs, card::valet | suits::carreaux,
								 card::dame | suits::trefles, card::dame | suits::piques, card::dame | suits::ceurs, card::dame | suits::carreaux,
								 card::roi | suits::trefles, card::roi | suits::piques, card::roi | suits::ceurs, card::roi | suits::carreaux,
								 card::tuz | suits::trefles, card::tuz | suits::piques, card::tuz | suits::ceurs, card::tuz | suits::carreaux };

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

	std::vector<std::shared_ptr<card_interface*>> cards_on_deck;
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
