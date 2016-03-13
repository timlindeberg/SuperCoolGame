#ifndef LAB3__GAME_OSTREAM
#define LAB3__GAME_OSTREAM

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <functional>

#include "Format.hpp"
#include "Utils.hpp"
#include "IO.hpp"

// Lazy macro
#define PRINT_BOX(color, message) Lab3::out << BeginBox(color) << message << EndBox()


namespace Lab3{

struct BeginBox{
	BeginBox(Format::Code color);

	Format::Code color; 
};

struct EndBox{};
struct Delimiter{};

struct Clear {};

struct MoveCursor {
	size_t lines;
	size_t columns;
	MoveCursor(int lines, int columns = 0);
};

enum class Alignment{
	LEFT,
	CENTER,
	RIGHT
};

class GameStream {
public:

	typedef std::basic_ostream<char, std::char_traits<char> > CoutType;
	typedef CoutType& (*StandardEndLine)(CoutType&);

	GameStream();

	template<class T>
	GameStream& operator<<(const T& t);

	GameStream& operator<<(StandardEndLine endl);
	GameStream& operator<<(const BeginBox& beginBox);
	GameStream& operator<<(const EndBox& endBox);
	GameStream& operator<<(const Delimiter& delimiter);
	GameStream& operator<<(const Clear& delimiter);
	GameStream& operator<<(const MoveCursor& delimiter);
	GameStream& operator<<(Alignment alignment);


	static const size_t WIDTH; 
	static const size_t OUTER_INDENT_WIDTH;
	static const size_t INDENT_WIDTH;
	static const int MAX_WIDTH;

	static const Format::Code ROOM_COLOR;
	static const Format::Code BATTLE_COLOR;
	static const Format::Code SUCCESS_COLOR;
	static const Format::Code FAIL_COLOR;

private:

	void PrintBar(const std::string& left, const std::string& middle, const std::string& right);
	void PrintLine(const std::string& str);
	std::vector<std::string> Partition(const std::string& text);
	size_t SplitWord(size_t n, std::string& word, std::vector<std::string>& lines);

	Format::Code _currentColor;
	Alignment _alignment;

	std::vector<std::string> _line;
	std::stringstream _ss;

	size_t _linesPrinted;
};

extern GameStream out;

}

#include "GameStream.tpp"

#endif