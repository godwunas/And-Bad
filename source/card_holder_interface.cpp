#include "card_holder_interface.h"
#include <algorithm>
#include <vector>

card_holder_interface::card_holder_interface()
	: cards_on_hand_(0)
{}

card_holder_interface::~card_holder_interface()
{}

void card_holder_interface::to_get_card(card_interface&& card, push_mode push_pos) {
	if (push_pos == push_mode::PUSH_FRONT)
		cards_on_hand_.push_front(std::move(card));
	else if (push_pos == push_mode::PUSH_BACK)
		cards_on_hand_.push_back(std::move(card));
}

card_interface&& card_holder_interface::to_send_card(const int& idx) {
	card_interface temp(std::move(cards_on_hand_[idx]));
	cards_on_hand_.pop_front();//т.к. мы перемещаем обьект, то найти соответствующий в контейнер remove не может, в следствии чего возвращает end, и очищается весь контейнер...пока не понятно как удалять с перемещением из середины...
	return std::move(temp);
}

void card_holder_interface::move_all_cards_to(card_holder_interface* owner, const push_mode& mode) {
	std::for_each(cards_on_hand_.begin(), cards_on_hand_.end(), [&owner, &mode](card_interface& card) { owner->to_get_card(std::move(card), mode); });
	cards_on_hand_.clear();
}