#ifndef CARD_INTERFACE_H
#define CARD_INTERFACE_H
#include <utility>
#include <cstdint>

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
		trefles	 = 0,//треф
		carreaux = 1,//бубны
		ceurs	 = 2,//червы
		piques	 = 3,//пики
	};

public:
	card_interface() :card_num_(0), card_suit_(0) {}
	explicit card_interface(uint16_t&& card_num, uint16_t&& card_suit) :card_num_(card_num), card_suit_(card_suit) {}
	~card_interface() {}

private:
	card_interface(const card_interface&) = delete;
	card_interface& operator=(const card_interface&) = delete;

public:
 	card_interface(card_interface&& other) {
		card_num_ = other.card_num_;
		other.card_num_ = 0;
		
		card_suit_ = other.card_suit_;
		other.card_suit_ = 0;
 	}

 	card_interface& operator=(card_interface&& other){
 		if (this != &other){
			card_num_ = other.card_num_;
			other.card_num_ = 0;

			card_suit_ = other.card_suit_;
			other.card_suit_ = 0;
 		}
 
 		return *this;
 	}

	//сравнение позиции	
	friend bool operator<(const card_interface& lhs, const card_interface& rhs) {
		return (lhs.card_num_ < rhs.card_num_);
	}

	//сравнение рубашки(масти)
	friend bool operator==(const card_interface& lhs, const card_interface& rhs) {
		return (lhs.card_suit_ == rhs.card_suit_);
	}
	
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

	bool is_trefles()	const noexcept { return card_suit_ & suits::trefles ? true : false; }
	bool is_carreaux()	const noexcept { return card_suit_ & suits::carreaux ? true : false; }
	bool is_ceurs()		const noexcept { return card_suit_ & suits::ceurs ? true : false; }
	bool is_piques()	const noexcept { return card_suit_ & suits::piques ? true : false; }

	static inline uint16_t get_first_card32_num() noexcept{ return card_nums::six; }
	static inline uint16_t get_first_card52_num() noexcept{ return card_nums::two; }
	static inline uint16_t get_last_card_num() noexcept { return card_nums::tuz; }
	static inline uint16_t get_suits_first() noexcept { return suits::trefles; }
	static inline uint16_t get_suits_last() noexcept { return suits::piques; }
	
private:	
	uint16_t card_num_  : 13;
	uint16_t card_suit_ : 2;
};

#endif