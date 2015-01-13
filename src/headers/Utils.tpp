template<class Stream, class T>
void Utils::PrintListInColors(Stream& out, const std::vector<T>& container,
	 const std::initializer_list<Format::Code>& colors){
	auto it = colors.begin();
	for(const auto& item : container){
		if(!Ptr(item)){
			std::cerr << "Container contains null!" << std::endl;
			continue;
		}

		out << (*it) << *Ptr(item) << Format::FG_DEFAULT << std::endl;

		// Wrap around
		if((++it) == colors.end()){
			it = colors.begin();
		}
	} 
}

template<typename T, typename Func>
bool Utils::ExecuteOnMatch(const std::vector<T>& objects, const std::string& name, Func f){
	for(const auto& item : objects){
		if(SameName(item, name)){
			f(*(Ptr(item)));
			return true;
		}
	}
	return false;
}

template<class T>
T* Utils::FindByName(const std::vector<std::unique_ptr<T>>& container, const std::string& name){
	for(auto& obj : container){
		if(SameName(obj, name)){
			return obj.get();
		}
	}
	return nullptr;
}

template<class T>
T* Utils::FindByName(const std::vector<T*>& container, const std::string& name){
	for(auto& obj : container){
		if(SameName(obj, name)){
			return obj;
		}
	}
	return nullptr;
}

template<class T, class U>
bool Utils::SameName(const T& t, const U& u){
	std::string tName = Ptr(t)->Name();
	std::string uName = Ptr(u)->Name();
	Utils::ToLowerCase(tName);
	Utils::ToLowerCase(uName);
	return tName == uName;
}

template<class T>
bool Utils::SameName(const T& t, const std::string& name){
	std::string tName = Ptr(t)->Name();
	std::string uName = name;
	Utils::ToLowerCase(tName);
	Utils::ToLowerCase(uName);
	return tName == uName;
}

template<class T>
void Utils::AddItem(std::vector<std::unique_ptr<T>>& container, std::unique_ptr<T>& ptr){
	container.push_back(std::move(ptr));
}

template<class T>
std::unique_ptr<T> Utils::RemoveItem(std::vector<std::unique_ptr<T>>& container,
 	const std::string& name){

	for(auto it = container.begin(); it != container.end(); ++it){
		if(Utils::SameName(*it, name)){
			std::unique_ptr<T> ptr = std::move(*it);
			container.erase(it);
			return ptr;
		} 
	}
	return std::unique_ptr<T>(nullptr);
}

template<class T>
T& Utils::RandomElement(std::vector<T> v){
	size_t index = RandomInt(0, v.size() - 1);
	return v[index];
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