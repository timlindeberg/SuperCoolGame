#include "Utils.hpp"

uint32_t Utils::seed = 1;
std::random_device Utils::rd;
std::mt19937 Utils::RNG = std::mt19937(seed);

std::vector<std::string> Utils::Split(const std::string& s, char delim){
	std::vector<std::string> v;
	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, delim)){
		v.push_back(item);
	}
	return v;
}

std::string Utils::Concatenate(const std::vector<std::string>& v){
	std::stringstream ss;
	for(auto& s : v){
		ss << s << ' ';
	}
	std::string s = ss.str();
	return Trim(s);
}

std::string& Utils::Trim(std::string& s) {
    return LeftTrim(RightTrim(s));
}

std::string& Utils::LeftTrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string& Utils::RightTrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string Utils::FileToString(const std::string& fileName){
	std::ifstream fstream(fileName);
	std::stringstream ss;
	ss << fstream.rdbuf();
	fstream.close();
	return ss.str();
}

std::string& Utils::Remove(std::string& s, char c){
	s.erase(std::remove(s.begin(), s.end(), c), s.end());
	return s;
}

std::string& Utils::Replace(std::string& s, char before, char after){
	std::replace(s.begin(), s.end(), before, after);
	return s;
}

std::string& Utils::ToLowerCase(std::string& s){
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

std::string& Utils::FirstUpperCase(std::string& s){
	if(s.size() == 0)
		return s;
	s[0] = std::toupper(s[0]);
	return s;
}

std::string& Utils::RemoveAnsiFormating(std::string& s){
	static std::regex regex("\033\\[(\\d*)m");
	static std::string compare = "\033";
	static std::string empty;
	if(s.find(compare) != std::string::npos){
		s = std::regex_replace(s, regex, empty);
	}
	return s;
}

size_t Utils::PrintSize(std::string s){
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	RemoveAnsiFormating(s);
	size_t numTabs = Utils::Count(s, '\t');
	std::wstring wide = converter.from_bytes(s);
	return wide.size() + numTabs * 4;
}

size_t Utils::Count(const std::string& s, char c){
	size_t count = 0;
	for(auto character : s){
		if(character == c){
			count++;
		}
	}
	return count;
}

std::vector<std::string>& Utils::RemoveBlankWords(std::vector<std::string>& v){
	for(auto it = v.begin(); it != v.end();) {
	    if (Utils::AllWhitespace(*it))
	        it = v.erase(it);
	    else
	    	++it;
	}
	return v;
}

bool Utils::AllWhitespace(const std::string& s){
	if(s == "")
		return true;
	
	for(char c : s){
		if(c != ' '){
			return false;
		}
	}
	return true;
} 


bool Utils::SameName(const std::string& t, const std::string& u){
	std::string tName = t;
	std::string uName = u;
	Utils::ToLowerCase(tName);
	Utils::ToLowerCase(uName);
	return tName == uName;
}

Format::Code Utils::PercentColor(double percentage){
	if(percentage < 0.33){
		return Format::RED;
	}else if(percentage >= 0.33 && percentage < 0.66){
		return Format::YELLOW;
	}else{
		return Format::GREEN;
	}
} 

int Utils::NormalDistInt(double mean, double stdDev){
    return static_cast<int>(round(NormalDistFloat(mean, stdDev)));
}

float Utils::NormalDistFloat(double mean, double stdDev){
    std::normal_distribution<float> dist(mean, stdDev);
    return dist(RNG);
}

int Utils::RandomInt(double min, double max){
    std::uniform_int_distribution<int> dist(min, max);
    return dist(RNG);
}

float Utils::RandomFloat(float min, float max){
    std::uniform_real_distribution<float> dist(min, max);
    return dist(RNG);
}

bool Utils::RandomBool(double probability){
    std::bernoulli_distribution dist(probability);
    return dist(RNG);
}

char Utils::RandomLetter() {
	static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return letters[RandomInt(0, sizeof(letters) - 1)];
}

