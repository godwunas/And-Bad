#ifndef CONSOLE_IO_CARD_H
#define CONSOLE_IO_CARD_H
#include <iostream>
#include <exception>
#include "card_interface.h"
#include <io.h>
#include <fcntl.h>
#include "player_interface.h"

struct bad_card_detected : std::exception {
};

void show_card(const card_interface& card) {
	_setmode(_fileno(stdout), _O_U16TEXT);

	if (card.is_two())
		std::wcout << 2;
	else if (card.is_three())
		std::wcout << 3;
	else if (card.is_four())
		std::wcout << 4;
	else if (card.is_five())
		std::wcout << 5;
	else if (card.is_six())
		std::wcout << 6;
	else if (card.is_seven())
		std::wcout << 7;
	else if (card.is_eight())
		std::wcout << 8;
	else if (card.is_nine())
		std::wcout << 9;
	else if (card.is_ten())
		std::wcout << 10;
	else if (card.is_valet())
		std::wcout << 'V';
	else if (card.is_dame())
		std::wcout << 'Q';
	else if (card.is_roi())
		std::wcout << 'K';
	else if (card.is_tuz())
		std::wcout << 'T';
	else {
		_setmode(_fileno(stdout), _O_TEXT);
		throw bad_card_detected();
	}

	if (card.is_trefles())
		std::wcout << wchar_t(0x2663);
	else if (card.is_carreaux())
		std::wcout << wchar_t(0x2666);
	else if (card.is_ceurs())
		std::wcout << wchar_t(0x2665);
	else if (card.is_piques())
		std::wcout << wchar_t(0x2660);
	else {
		_setmode(_fileno(stdout), _O_TEXT);
		throw bad_card_detected();
	}

	std::wcout << std::endl;

	_setmode(_fileno(stdout), _O_TEXT);
}	

void show_player_name(player_interface* pl) {
	std::cout << " " << pl->get_name() << std::endl << std::endl;
}


#endif
