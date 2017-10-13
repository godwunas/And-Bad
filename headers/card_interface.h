#ifndef CARD_INTERFACE_H
#define CARD_INTERFACE_H
#include <utility>
#include <cstdint>
#include <string>

class player_interface;
class card_interface;

struct do_not_have_player_owner : public std::exception {
	do_not_have_player_owner(const card_interface* const card) :exception(), card_(card), ex_error_("card has no player owner") {}

	const card_interface* card_;
	std::string ex_error_;
};

class card_interface{
protected:
	enum card_nums{		
		two		= 0x000001,
		three	= 0x000002,
		four	= 0x000004,
		five	= 0x000008,
		six		= 0x000010,
		seven	= 0x000020,
		eigth	= 0x000040,
		nine	= 0x000080,
		ten		= 0x000100,
		//face cards
		valet	= 0x000200,//knave or jack
		dame	= 0x000400,//lady or queen
		roi		= 0x000800,//king
		tuz		= 0x001000,
	};

	//масть
	enum suits{
		trefles		= 0x000001,//треф
		carreaux	= 0x000002,//бубны
		ceurs		= 0x000004,//червы
		piques		= 0x000008,//пики
	};

public:
	card_interface();
	card_interface(uint16_t&& card_num, uint16_t&& card_suit);
	~card_interface() = default;

private:
	card_interface(const card_interface&) = delete;
	card_interface& operator=(const card_interface&) = delete;

public:
	card_interface(card_interface&& other);
	card_interface& operator=(card_interface&& other);

	//сравнение на равенство позиции	
	friend bool is_equal_pos(const card_interface& lhs, const card_interface& rhs) noexcept{
		return (lhs.card_num_ & rhs.card_num_ ? true : false);
	}

	//сравнение на факт вычисления младшей позиции
	friend bool is_less_pos(const card_interface& lhs, const card_interface& rhs) noexcept{
		return lhs.card_num_ < rhs.card_num_;
	}

	//сравнение на одинаковость рубашки(масти)
	friend bool is_equal_suit(const card_interface& lhs, const card_interface& rhs) noexcept {
		return (lhs.card_suit_ & rhs.card_suit_ ? true : false);
	}

	//необходим для алгоритмов, for example: std::erase
	friend bool operator==(const card_interface& lhs, const card_interface& rhs) noexcept {
		return is_equal_pos(lhs, rhs) && is_equal_suit(lhs, rhs);
	}
	
	//метод-идентификации соответствующей позиции карты
	bool is_two()	const noexcept { return card_num_ & card_nums::two ? true : false; }
	bool is_three() const noexcept { return card_num_ & card_nums::three ? true : false; }
	bool is_four()	const noexcept { return card_num_ & card_nums::four ? true : false; }
	bool is_five()	const noexcept { return card_num_ & card_nums::five ? true : false; }
	bool is_six()	const noexcept { return card_num_ & card_nums::six ? true : false; }
	bool is_seven() const noexcept { return card_num_ & card_nums::seven ? true : false; }
	bool is_eigth() const noexcept { return card_num_ & card_nums::eigth ? true : false; }
	bool is_nine()	const noexcept { return card_num_ & card_nums::nine ? true : false; }
	bool is_ten()	const noexcept { return card_num_ & card_nums::ten ? true : false; }
	bool is_valet() const noexcept { return card_num_ & card_nums::valet ? true : false; }
	bool is_dame()	const noexcept { return card_num_ & card_nums::dame ? true : false; }
	bool is_roi()	const noexcept { return card_num_ & card_nums::roi ? true : false; }
	bool is_tuz()	const noexcept { return card_num_ & card_nums::tuz ? true : false; }

	//метод-идентификации соответствующей масти карты
	bool is_trefles()	const noexcept { return card_suit_ & suits::trefles ? true : false; }
	bool is_carreaux()	const noexcept { return card_suit_ & suits::carreaux ? true : false; }
	bool is_ceurs()		const noexcept { return card_suit_ & suits::ceurs ? true : false; }
	bool is_piques()	const noexcept { return card_suit_ & suits::piques ? true : false; }

	static inline uint16_t get_first_card32_num()	noexcept	{ return card_nums::six; }
	static inline uint16_t get_first_card52_num()	noexcept	{ return card_nums::two; }
	static inline uint16_t get_last_card_num()		noexcept	{ return card_nums::tuz; }
	static inline uint16_t get_suits_first()		noexcept	{ return suits::trefles; }
	static inline uint16_t get_suits_last()			noexcept	{ return suits::piques; }

	//задать владельца-игрока карты
	void set_owner_player(player_interface* pl);
	//узнать владельца-игрока карты
	player_interface* get_owner_player() const;
	
private:	
	uint16_t card_num_;
	uint16_t card_suit_;
	player_interface* owner_player_;
};

#endif
