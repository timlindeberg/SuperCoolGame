template<class T>
void Utils::PrintListInColors(std::ostream& os, const std::vector<T>& container,
	 const std::initializer_list<Format::Code>& colors){
	auto it = colors.begin();
	for(const auto& item : container){
		if(!Ptr(item)){
			std::cerr << "Container contains null!" << std::endl;
			continue;
		}

		os << "\t" << (*it) << *Ptr(item) << Format::FG_DEFAULT << std::endl;

		// Wrap around
		if((++it) == colors.end()){
			it = colors.begin();
		}
	} 
}

template<typename T, typename Func>
bool Utils::ExecuteOnMatch(const std::vector<T>& objects, const std::string& name, Func f){
	for(const auto& item : objects){
		if(Ptr(item)->Name() == name){
			f(*(Ptr(item)));
			return true;
		}
	}
	return false;
}

template<class T>
T* Utils::Ptr(const std::unique_ptr<T>& obj){
	return obj.get();
}

template<class T>
T* Utils::Ptr(T& obj){
	return &obj;
}

template<class T>
T* Utils::Ptr(T* obj){
	return obj;
}