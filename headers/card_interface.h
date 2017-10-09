#ifndef CARD_INTERFACE_H
#define CARD_INTERFACE_H
#include <utility>
#include <cstdint>

class card_interface{
public:
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
		trefles	 = 0x001000,//треф
		carreaux = 0x002000,//бубны
		ceurs	 = 0x004000,//червы
		piques	 = 0x008000,//пики
	};

	card_interface() :card_info_(0) {}
	explicit card_interface(uint16_t&& card_info) :card_info_(card_info) {}
	~card_interface() {}

private:
	card_interface(const card_interface&) = delete;
	card_interface& operator=(const card_interface&) = delete;

public:
 	card_interface(card_interface&& other)
		:card_info_(0){
		std::swap(card_info_, other.card_info_);
 	}

 	card_interface& operator=(card_interface&& other){
 		if (this != &other){
			card_info_ = 0;
			std::swap(card_info_, other.card_info_);
 		}
 
 		return *this;
 	}

	friend bool operator<(const card_interface& lhs, const card_interface& rhs) {
		return ((lhs.card_info_ << 4) < (rhs.card_info_ << 4));
	}

	friend bool operator==(const card_interface& lhs, const card_interface& rhs) {
		return (lhs.card_info_ & rhs.card_info_);
	}

	bool is_two()	const noexcept { return card_info_ & card_nums::two; }
	bool is_three() const noexcept { return card_info_ & card_nums::three; }
	bool is_four()	const noexcept { return card_info_ & card_nums::four; }
	bool is_five()	const noexcept { return card_info_ & card_nums::five; }
	bool is_six()	const noexcept { return card_info_ & card_nums::six; }
	bool is_seven() const noexcept { return card_info_ & card_nums::seven; }
	bool is_eigth() const noexcept { return card_info_ & card_nums::eigth; }
	bool is_nine()	const noexcept { return card_info_ & card_nums::nine; }
	bool is_ten()	const noexcept { return card_info_ & card_nums::ten; }
	bool is_valet() const noexcept { return card_info_ & card_nums::valet; }
	bool is_dame()	const noexcept { return card_info_ & card_nums::dame; }
	bool is_roi()	const noexcept { return card_info_ & card_nums::roi; }
	bool is_tuz()	const noexcept { return card_info_ & card_nums::tuz; }

	bool is_trefles()	const noexcept { return card_info_ & suits::trefles; }
	bool is_carreaux()	const noexcept { return card_info_ & suits::carreaux; }
	bool is_ceurs()		const noexcept { return card_info_ & suits::ceurs; }
	bool is_piques()	const noexcept { return card_info_ & suits::piques; }

private:	
	uint16_t card_info_;
};

#endif