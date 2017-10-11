#ifndef DRINKER_GAME_H
#define DRINKER_GAME_H

namespace drinker{
	class drinker_game{

	public:
		drinker_game();
		~drinker_game() = default;

	private:
		drinker_game(const drinker_game&) = delete;
		drinker_game& operator=(const drinker_game&) = delete;
	};
}

#endif