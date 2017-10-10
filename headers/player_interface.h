#ifndef PLAYER_INTERFACE_H
#define PLAYER_INTERFACE_H
#include "card_holder_interface.h"
#include <vector>
#include <algorithm>

class player_interface : public card_holder_interface{

public:
	player_interface() = default;
	virtual ~player_interface() = default;
private:
	player_interface(const player_interface&) = delete;
	player_interface& operator=(const player_interface&) = delete;

public:
	virtual void make_move() = 0;
};

#endif