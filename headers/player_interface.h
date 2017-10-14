#ifndef PLAYER_INTERFACE_H
#define PLAYER_INTERFACE_H
#include "card_holder_interface.h"
#include "card_deck.h"
#include <string>

class player_interface : public card_holder_interface{

public:
	player_interface() :active_player_(true), name_(""){}
	virtual ~player_interface() = default;
private:
	player_interface(const player_interface&) = delete;
	player_interface& operator=(const player_interface&) = delete;

public:
	//метод хода игрока
	virtual void make_move() = 0;
	virtual void init_name() = 0;

	inline bool	is_active_player()		const		{ return active_player_; }
	inline void set_inactive_player()	noexcept	{ active_player_ = false; }
	inline const std::string& get_name() const noexcept { return name_; }

	//переопределенный метод получения карты
	virtual void to_get_card(card_interface&& card, push_mode push_pos) override;

protected:
	std::string name_;
private:
	bool		active_player_;
};

#endif