#ifndef CARD_HOLDER_INTERFACE_H
#define CARD_HOLDER_INTERFACE_H
#include "card_interface.h"
#include <deque>
#include <algorithm>

//��������� ���������� �����(�����, ����, ������(?), ����)
class card_holder_interface{
protected:
	enum class push_mode : int{
		PUSH_FRONT = 0,
		PUSH_BACK,
	};
public:
	card_holder_interface() : cards_on_hand(0) {}
	virtual ~card_holder_interface() = 0;
private:
	card_holder_interface(const card_holder_interface&) = delete;
	card_holder_interface& operator=(const card_holder_interface&) = delete;

public:
	virtual void to_get_card(card_interface&& card, push_mode push_pos) { 
		if (push_pos == push_mode::PUSH_FRONT)
			cards_on_hand.push_front(std::move(card));
		else if (push_pos == push_mode::PUSH_BACK)
			cards_on_hand.push_back(std::move(card)); 
	}
	bool is_dont_have_card() const noexcept { return cards_on_hand.empty(); }
	card_interface&& to_send_card(const int& idx) {
		card_interface temp(std::move(cards_on_hand[idx]));
		cards_on_hand.erase(cards_on_hand.begin(), std::remove(cards_on_hand.begin(), cards_on_hand.end(), temp));
		return std::move(temp);
	}

protected:
	std::deque<card_interface> cards_on_hand;
};

#endif