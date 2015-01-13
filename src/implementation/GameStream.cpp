#include "GameStream.hpp"

namespace Lab3 {

GameStream out;

const size_t GameStream::WIDTH 			= 60; 
const size_t GameStream::INDENT_WIDTH	= 2;

const int GameStream::MAX_WIDTH			= WIDTH - 2 * (INDENT_WIDTH + 1);
static_assert(GameStream::MAX_WIDTH >= 0, "MAX_WIDTH less than zero!");

const Format::Code GameStream::ROOM_COLOR			= Format::CYAN;
const Format::Code GameStream::BATTLE_COLOR			= Format::YELLOW;
const Format::Code GameStream::SUCCESS_COLOR 		= Format::BLUE;
const Format::Code GameStream::FAIL_COLOR 			= Format::RED;

BeginBox::BeginBox(Format::Code color) : color(color) {}

//╭──────────────────╮
//├╴╴╴╴╴╴╴╴╴╶╶╶╶╶╶╶╶╶┤
//╰──────────────────╯
//╭─────────────────╮
//├╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌┤
//╰─────────────────╯
//╭─────────────────╮
//├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤
//╰─────────────────╯
//╭─────────────────╮
//├┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┤
//╰─────────────────╯

MoveCursor::MoveCursor(int lines, int columns) : lines(lines), columns(columns) {}

GameStream::GameStream() : 
	_currentColor(Format::FG_DEFAULT),
	_alignment(Alignment::LEFT),
	_ss()
{}

void GameStream::PrintBar(const std::string& left, const std::string& middle, const std::string& right){
	std::cout << _currentColor;
	std::cout << left;
	for(size_t i = 0; i < WIDTH - 2; ++i){
		std::cout << middle;
	}
	std::cout << right;
	std::cout << Format::FG_DEFAULT << std::endl;
	++_linesPrinted;
}

void GameStream::PrintLine(const std::string& str) {
	auto PrintWhiteSpaces = [] (size_t num) { 
		for(size_t i = 0; i < num; ++i ){
				std::cout << ' ';
		}
	};

	std::cout << _currentColor << "│" << Format::FG_DEFAULT;
	PrintWhiteSpaces(INDENT_WIDTH);

	size_t printSize = Utils::PrintSize(str);
	if(printSize > MAX_WIDTH){
		return;
	}

	size_t fill = MAX_WIDTH - printSize;

	switch(_alignment){
		case Alignment::LEFT:
		{
			std::cout << str;
			PrintWhiteSpaces(fill);
			break;
		}
		case Alignment::CENTER:
		{
			PrintWhiteSpaces(fill / 2);
			std::cout << str;
			PrintWhiteSpaces(fill / 2);
			if(fill % 2 != 0) std::cout << ' ';
			break;
		}
		case Alignment::RIGHT:
		{
			PrintWhiteSpaces(fill);
			std::cout << str;
			break;
		}

	}
	PrintWhiteSpaces(INDENT_WIDTH);
	std::cout << _currentColor << "│" << Format::FG_DEFAULT << std::endl;
	++_linesPrinted;
}

std::vector<std::string> GameStream::Partition(const std::string& text){
	std::vector<std::string> lines;

	if(text.size() < MAX_WIDTH){
		lines.push_back(text);
		return lines;
	}

	std::vector<std::string> words = Utils::Split(text);
	std::stringstream stringBuilder;

	size_t currentWidth = 0;
	for(auto& word : words){
		size_t n = Utils::PrintSize(word) + 1;
		//n = SplitWord(n, word, lines);
		if(currentWidth + n > MAX_WIDTH){
			currentWidth = n;
			std::string lol = stringBuilder.str();
			lines.push_back(stringBuilder.str());
			stringBuilder.str("");
			stringBuilder.clear();
			stringBuilder << word << ' ';
			continue;
		}
		stringBuilder << word << ' ';
		currentWidth += n;
	}
	if(currentWidth != 0)
		lines.push_back(stringBuilder.str());
	
	for_each(lines.begin(), lines.end(), &Utils::Trim);
	return lines;
}

size_t GameStream::SplitWord(size_t n, std::string& word, std::vector<std::string>& lines){
	static std::regex regex("\033\\[(\\d*)m");
	static std::string compare = "\033";
	static std::string empty;

	while(n > MAX_WIDTH){

		std::string ansiremoved;
		std::smatch sm;
		if(word.find(compare) != std::string::npos){
			std::regex_search(word, sm, regex);
			ansiremoved = std::regex_replace(word, regex, empty);
		}
		auto begin = word.begin();
		auto end = word.begin() + MAX_WIDTH - 1;
		std::string firstPart = word.substr(0, MAX_WIDTH - 1);
		word.erase(begin, end);
		firstPart.append("-");
		lines.push_back(firstPart);
		n = Utils::PrintSize(word) + 1;
	}


	return n;
}

GameStream& GameStream::operator<<(StandardEndLine endl){
	using namespace std::placeholders;
	std::vector<std::string> lines = Partition(_ss.str());
	_ss.str("");
	_ss.clear();
	auto printLineFunction = std::bind(&GameStream::PrintLine, this, _1);
	std::for_each(lines.begin(), lines.end(), printLineFunction);
	_alignment = Alignment::LEFT; // Reset _alignment for next row
	return *this;
}

GameStream& GameStream::operator<<(const BeginBox& beginBox){
	_currentColor = beginBox.color;
	PrintBar("╭", "─", "╮");
	return *this;
}

GameStream& GameStream::operator<<(const EndBox& endBox){
	PrintBar("╰", "─", "╯");
	return *this;
}

GameStream& GameStream::operator<<(const Delimiter& delimiter){
	PrintBar("├", "╌", "┤");
	return *this;
}
GameStream& GameStream::operator<<(const MoveCursor& moveCursor){
	int lines = moveCursor.lines;
	int columns = moveCursor.columns;
	if(lines != 0){
		std::cout << "\033[" << std::abs(lines) << (lines < 0 ? "A" : "B");
	}
	if(columns != 0){
		std::cout << "\033[" << std::abs(columns) << (columns < 0 ? "D" : "C");
	}
	return *this;
}

GameStream& GameStream::operator<<(const Clear& clear){
	for(size_t i = 0; i < _linesPrinted; ++i){
		std::cout << "\033[1A";	// Move line up by one
		std::cout << "\033[K";	// Erase line
	}

	_linesPrinted = 0;
	return *this;
}

GameStream& GameStream::operator<<(Alignment alignment){
	_alignment = alignment;
	return *this;
}

}
