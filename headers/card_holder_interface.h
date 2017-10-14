#ifndef CARD_HOLDER_INTERFACE_H
#define CARD_HOLDER_INTERFACE_H
#include "card_interface.h"
#include <deque>

//��������� ���������� �����(�����, ����, ������(?), ����)
class card_holder_interface{
protected:
	enum class push_mode : int{
		PUSH_FRONT = 0,
		PUSH_BACK,
	};
public:
	card_holder_interface();
	virtual ~card_holder_interface() = 0;
private:
	card_holder_interface(const card_holder_interface&) = delete;
	card_holder_interface& operator=(const card_holder_interface&) = delete;

public:
	//����� ��������� �����(���������� � "������ �� �����", �.�. � cards_on_hand)
	virtual void to_get_card(card_interface&& card, push_mode push_pos);
	//����� ��� ��������� ��������� "������ ������"
	bool is_dont_have_card() const noexcept { return cards_on_hand_.empty(); }
	//����� ������ ����� �� ������ ���������
	card_interface to_send_card(const int& idx);
	//����� �������� ���� ���� ������� ���������
	void move_all_cards_to(card_holder_interface* owner, const push_mode& mode);

protected:
	std::deque<card_interface> cards_on_hand_;
};

#endif