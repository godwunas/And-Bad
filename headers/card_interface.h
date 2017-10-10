#ifndef CARD_INTERFACE_H
#define CARD_INTERFACE_H
#include <utility>
#include <cstdint>

class card_interface{
protected:
	enum card_nums{		
		two		= 0x000000,
		three	= 0x000001,
		four	= 0x000002,
		five	= 0x000004,
		six		= 0x000008,
		seven	= 0x000010,
		eigth	= 0x000020,
		nine	= 0x000040,
		ten		= 0x000080,
		//face cards
		valet	= 0x000100,//knave or jack
		dame	= 0x000200,//lady or queen
		roi		= 0x000400,//king
		tuz		= 0x000800,
	};

	//масть
	enum suits{
		trefles	 = 0x000000,//треф
		carreaux = 0x000001,//бубны
		ceurs	 = 0x000002,//червы
		piques	 = 0x000004,//пики
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
		other.card_suit_;
 	}

 	card_interface& operator=(card_interface&& other){
 		if (this != &other){
			card_num_ = other.card_num_;
			other.card_num_ = 0;

			card_suit_ = other.card_suit_;
			other.card_suit_;
 		}
 
 		return *this;
 	}

	friend bool operator<(const card_interface& lhs, const card_interface& rhs) {
		return (lhs.card_num_ < rhs.card_num_);
	}

	friend bool operator==(const card_interface& lhs, const card_interface& rhs) {
		return ((lhs.card_num_ & rhs.card_num_) && (lhs.card_suit_ & lhs.card_suit_));
	}
	
	bool is_two()	const noexcept { return card_num_ & card_nums::two; }
	bool is_three() const noexcept { return card_num_ & card_nums::three; }
	bool is_four()	const noexcept { return card_num_ & card_nums::four; }
	bool is_five()	const noexcept { return card_num_ & card_nums::five; }
	bool is_six()	const noexcept { return card_num_ & card_nums::six; }
	bool is_seven() const noexcept { return card_num_ & card_nums::seven; }
	bool is_eigth() const noexcept { return card_num_ & card_nums::eigth; }
	bool is_nine()	const noexcept { return card_num_ & card_nums::nine; }
	bool is_ten()	const noexcept { return card_num_ & card_nums::ten; }
	bool is_valet() const noexcept { return card_num_ & card_nums::valet; }
	bool is_dame()	const noexcept { return card_num_ & card_nums::dame; }
	bool is_roi()	const noexcept { return card_num_ & card_nums::roi; }
	bool is_tuz()	const noexcept { return card_num_ & card_nums::tuz; }

	bool is_trefles()	const noexcept { return card_suit_ & suits::trefles; }
	bool is_carreaux()	const noexcept { return card_suit_ & suits::carreaux; }
	bool is_ceurs()		const noexcept { return card_suit_ & suits::ceurs; }
	bool is_piques()	const noexcept { return card_suit_ & suits::piques; }

	static inline uint16_t get_first_card32_num() noexcept{ return card_nums::six; }
	static inline uint16_t get_first_card52_num() noexcept{ return card_nums::two; }
	static inline uint16_t get_last_card_num() noexcept { return card_nums::tuz; }
	static inline uint16_t get_suits_first() noexcept { return suits::trefles; }
	static inline uint16_t get_suits_last() noexcept { return suits::piques; }
	
private:	
	uint16_t card_num_  : 12;
	uint16_t card_suit_ : 4;
};

#endif