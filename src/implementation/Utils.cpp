#include "Utils.hpp"

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

