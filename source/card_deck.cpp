#include "card_deck.h"
#include <random>
#include <algorithm>

card_deck* card_deck::single_deck = nullptr;
card_deck_destroy card_deck::card_deck_destr;
card_count card_deck::card_count_ = card_count::normal_mode;
heap_out_cards* card_deck::heap_out_card_ = nullptr;

card_deck_destroy::~card_deck_destroy()
{
	if (single_deck != nullptr)
		delete single_deck;
}

card_deck::card_deck(const card_count count) :add_card_(false) {
	card_count_ = count;
	cards_on_hand.resize(static_cast<size_t>(card_count_));
}

void card_deck_destroy::initialize(card_deck* card_deck_ptr)
{
	if (card_deck_ptr != nullptr)
		single_deck = card_deck_ptr;
}

card_deck& card_deck::getInstance(const card_count count_card){
	if (single_deck == nullptr){
		single_deck = new card_deck(count_card);
		heap_out_card_ = new heap_out_cards;
		card_deck_destr.initialize(single_deck);
	}

	GetHeapOutCard();

	return *single_deck;
}

heap_out_cards& card_deck::GetHeapOutCard(){
	if (heap_out_card_ == nullptr)
		heap_out_card_ = new heap_out_cards;

	return *heap_out_card_; 
}

card_deck::~card_deck() {
	if (heap_out_card_ != nullptr)
		delete heap_out_card_;
}

void card_deck::card_add(){
	using c_i = card_interface;
	
	for (auto i = card_count_ == normal_mode ? c_i::get_first_card32_num() : c_i::get_first_card52_num(); i <= c_i::get_last_card_num(); i <<= 1)
		for (auto j = c_i::get_suits_first(); i <= c_i::get_suits_last(); j <<= 1)
			cards_on_hand.emplace_back(c_i(std::move(i), std::move(j)));
}

void card_deck::card_mix() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::shuffle(cards_on_hand.begin(), cards_on_hand.end(), mt);
}

void card_deck::reset(){
	if (!add_card_){
		card_add();
		add_card_ = true;
	}
	if (heap_out_card_ != nullptr){
		std::for_each(heap_out_card_->cards_on_hand.begin(), heap_out_card_->cards_on_hand.end(), [](card_interface& card){single_deck->to_get_card(std::move(card), push_mode::PUSH_BACK); });
	}
	card_mix();
}