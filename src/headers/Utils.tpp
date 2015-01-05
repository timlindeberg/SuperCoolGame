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