//////////////////////////////////////////////////////////////////////////////
// tablefile.hpp
// Copyright (c) 2012 by Alexander Kuslya

#ifndef SCIENCE_IO_TABLEFILE_HPP_INCLUDED
#define SCIENCE_IO_TABLEFILE_HPP_INCLUDED


#include <science/core/type.hpp>

#include <fstream>
#include <sstream>
#include <iomanip>


/*!***************************************************************************** 
	@brief Макросы для упрощения работы с science::Pair классом
	@param value - записываемое в файл значение
	@param width - число символов, выделяемых под записываемое значение
	@param precision - точность записывамой величины
	
	Макросы предназначены для сокращения записи, при вызове science::Pair. 
    Используются в тех случаях, когда имя переменной и форма его записи в шапке
    файла одинаковые.
    Пример 1: вместо << science::Pair(Mach, "Mach") вызываем << SCIENCE_PAIR(Mach)
    Результат в файле будет одинаковым
    Пример 2: вместо << science::Pair(Mach, "Mach", 15, 4) вызываем 
    << SCIENCE_PAIR_WP(Mach, 15, 4). Результат в файле будет одинаковым
*******************************************************************************/
#ifndef SCIENCE_PAIR
#define SCIENCE_PAIR(value) science::Pair((value), #value)
#endif

#ifndef SCIENCE_PAIR_WP
#define SCIENCE_PAIR_WP(value, width, precision) science::Pair((value), #value, (width), (precision))
#endif



/** \brief science - Common utilities library */
namespace science {


namespace detail {
	typedef std::basic_ostream<char, std::char_traits<char> > otype_;
	typedef otype_& (*stdmanipulator_)(otype_&);
}


/* Pre-Define */
class Pair;
class TableFile;


//////////////////////////////////////////////////////////////////////////////
class Formator
{
    Formator();

    static Pair mpair;

public:
    static Pair const& do_format(
          TableFile const&
        , Pair const&
        );
};


//////////////////////////////////////////////////////////////////////////////
enum HeadMode {_single, _multi, _none};	
	

/*
@   Structure 'Pair'
@   Helpful class for providing of formated output
@   Using as argument of operator << (TableFile&, Pair);
*/
//////////////////////////////////////////////////////////////////////////////
class Pair
{
    unsigned width_;
    unsigned precision_;

    sreal_t value_;
    std::string name_;

    friend class Formator;

public:
    enum FormatPriority {
          _low
        , _high
    };

    enum NumerationT {
          _decimal
        , _octal
        , _hexadecimal
    };

private:
    FormatPriority priority_;
    NumerationT numeration_t_;

public:
    Pair(
          sreal_t const value
        , std::string const cell_name
        , NumerationT const numeration = _decimal
        );

    Pair(
		  sreal_t const value
		, std::string const cell_name
		, unsigned const width
		, unsigned const precision
        , NumerationT const numeration = _decimal
		);
	
    unsigned const width() const;
    unsigned const precision() const;
    
    sreal_t const value() const;
    std::string const name() const;

    NumerationT const numeration() const;
};



/*
@ Declaration for define output operators as friends
*/
class TableFile;

//////////////////////////////////////////////////////////////////////////////
TableFile& operator << (TableFile&, Pair const& pair);
TableFile& operator << (TableFile&, detail::stdmanipulator_ const& manip);


/*
@   Class TableFile
@   Provides formated output to file
@   Is an inheritor of std::ofstream 
*/
//////////////////////////////////////////////////////////////////////////////
class TableFile: public std::ofstream
{
    friend class Formator;

	std::ostringstream headbuff_;
	std::ostringstream linebuff_;

    bool first_print_;
	bool is_date_print_;	

    HeadMode head_mode_;

    unsigned line_number_;		
	unsigned head_step_;
    unsigned hiter_;

    std::string files_name_;
    std::wstring wfiles_name_;

    static unsigned global_width_;
    static unsigned global_precision_;
    static unsigned global_head_step_;

    unsigned width_;
    unsigned precision_;

    /*
        @ friend declaration of output operators
    */
    friend TableFile& operator << (TableFile&, Pair const& pair);
    friend TableFile& operator << (TableFile&, detail::stdmanipulator_ const& manip);

public:
	explicit TableFile(HeadMode const& head_mode = _single);

	explicit TableFile(
          char const* fname
        , std::ios_base::openmode const mode = std::ios_base::out
        , HeadMode const& head_mode = _single
        );

    explicit TableFile(
          std::string const fname
        , std::ios_base::openmode const mode = std::ios_base::out
        , HeadMode const& head_mode = _single
        );

    explicit TableFile(
         wchar_t const* fname
        , std::ios_base::openmode const mode = std::ios_base::out
        , HeadMode const& head_mode = _single
        );

    ~TableFile();

    explicit TableFile(
          std::wstring const fname
        , std::ios_base::openmode const mode = std::ios_base::out
        , HeadMode const& head_mode = _single
        );

	void close();

	void open(
          char const* fname
        , std::ios_base::openmode const mode = std::ios_base::out
        , HeadMode const& head_mode = _single
        );

    void open(
          std::string const fname
        , std::ios_base::openmode const mode = std::ios_base::out
        , HeadMode const& head_mode = _single
        );

    void open(
         wchar_t const* fname
        , std::ios_base::openmode const mode = std::ios_base::out
        , HeadMode const& head_mode = _single
        );

    void open(
          std::wstring const fname
        , std::ios_base::openmode const mode = std::ios_base::out
        , HeadMode const& head_mode = _single
        );

    std::string const get_files_name() const;
    std::wstring const get_wfiles_name() const;

	void set_date_print(bool const is_print);
    bool const get_date_print() const;

	void set_head_print_mode(HeadMode const mode);
    HeadMode const get_head_print_mode() const;

    /*
    @   Decimation of head output in _multi head print mode
    @   step_number means: print head every 'step_number'
    */
	void set_step_head_print(unsigned const step_number);
    unsigned const get_step_head_print() const;

    void set_width(unsigned const new_width);
    unsigned const get_width() const;

    void set_precision(unsigned const new_precision);
    unsigned const get_precision() const;

    static void set_global_width(unsigned const new_width);
    static unsigned const get_global_width();

    static void set_global_precision(unsigned const new_precision);
    static unsigned const get_global_precision();

private:
	void set_buffer(Pair const& p);
	void add_to_buffer(Pair const& p);

    bool const is_first_print() const;
};
	

} /* namespace science */


#endif
