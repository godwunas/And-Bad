#ifndef PLAYER_INTERFACE_H
#define PLAYER_INTERFACE_H
#include "card_holder_interface.h"
#include "card_deck.h"

class player_interface : public card_holder_interface{

public:
	player_interface() :active_player_(true){}
	virtual ~player_interface() = default;
private:
	player_interface(const player_interface&) = delete;
	player_interface& operator=(const player_interface&) = delete;

public:
	virtual void make_move() = 0;

	inline bool	is_active_player() const { return active_player_; }
	inline void set_inactive_player() noexcept { active_player_ = false; }

	virtual void to_get_card(card_interface&& card, push_mode push_pos) override{
		card.set_owner_player(this);
		card_holder_interface::to_get_card(std::move(card), push_pos);
	}

private:
	bool	active_player_;
};

#endif