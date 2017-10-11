#ifndef CARD_DECK_H
#define CARD_DECK_H
#include "card_holder_interface.h"
#include <vector>
#include <memory>

enum card_count {
	normal_mode = 36,
	maximize_mode = 54
};

class card_deck_destroy;
class heap_out_cards;

//колода карт в виде синглтона + использование общего интерфейса отдачи получения карты через card_holder_interface
class card_deck : public card_holder_interface{
public:
	static card_deck& getInstance(const card_count count_card);
	void InstanceHeapCards(heap_out_cards* heap_cards);

private:
	card_deck(const card_count count);
	~card_deck();
	card_deck& operator=(card_deck&& op) = delete;
	card_deck operator=(card_deck& op) = delete;
	card_deck(card_deck& op) = delete;
	card_deck(card_deck&& op) = delete;

	card_count card_count_; //количество карт в колоде
	static card_deck* single_deck; 
	static card_deck_destroy card_deck_destr;
	static heap_out_cards* heap_out_card_;
	friend class card_deck_destroy;

	//перемешиваем карты
	void card_mix();
	//добавляем нужное кол-во карт
	void card_add();
};

class card_deck_destroy {
private:
	card_deck* single_deck;
public:
	~card_deck_destroy();
	void initialize(card_deck* card_deck_ptr);
};


//Бита
class heap_out_cards : public card_holder_interface{
private:
	heap_out_cards() = default;
	~heap_out_cards() = default;
	heap_out_cards& operator=(const heap_out_cards&) = delete;
	heap_out_cards&& operator=(const heap_out_cards&&) = delete;
	heap_out_cards(const heap_out_cards&) = delete;
	heap_out_cards(const heap_out_cards&&) = delete;
	friend class card_deck;

	static heap_out_cards* heap_cards_;
};
#endif
