namespace Lab3{

template<class T> typename IO::Factory<T>::CreationMap* IO::Factory<T>::map = nullptr;

//----------------------------------------------
// Factory
//----------------------------------------------

template<class T>
std::unique_ptr<T> IO::Factory<T>::CreateInstance(const std::string& className){
	if(!map){
		std::cout << "Class " << className << " is not registered!" << std::endl;
	}
	if(!(*map).count(className)){
		std::cout << "Invalid class name : " << className << std::endl;
	}
	return (*map)[className]();
}

template<class T>
typename IO::Factory<T>::CreationMap* IO::Factory<T>::GetMap(){
	if(!map){
		map = new CreationMap;	
	} 
	return map;
}

template<class T>
IO::FactoryRegistration<T>::FactoryRegistration(const std::string& s) {
	(*GetMap())[s] = &IO::CreateInstance<T>;
}

template<class T>
std::unique_ptr<T> IO::CreateInstance(){
	return std::unique_ptr<T>(new T);
}

//----------------------------------------------
// IO
//----------------------------------------------

template<class T>
std::unique_ptr<T> IO::ParseObject(std::istream& is){
	std::stringstream ss;
	ss << ReadObject(is); 
	std::string type;
	if(!(ss >> type)){
		std::string error = "Failed to read type of object type ";
		error.append(typeid(T).name());
		throw std::invalid_argument(error);
	}
	std::unique_ptr<T> ptr = IO::Factory<T>::CreateInstance(type);
	std::string name;
	if(!(ss >> name)){
		std::string error = "Failed to parse name of object of type ";
		error.append(typeid(T).name());
		throw std::invalid_argument(error);
	}
	ptr->SetName(name);	

	if(!(ss >> *ptr)){
		std::string error = "Failed to parse object of type ";
		error.append(typeid(T).name());
		throw std::invalid_argument(error);
	}
	return ptr;
}

template<class T>
std::vector<std::unique_ptr<T>> IO::ParseList(std::istream& is){
	std::stringstream ss;
	ss << ReadList(is);
	std::vector<std::unique_ptr<T>> v;
	if(ss.str() == ""){
		// Empty list
		return v;
	}

	std::string tmp;
	do{
		v.push_back(std::move(IO::ParseObject<T>(ss)));
	}while((ss >> tmp) && tmp[0] == IO::LIST_SEP);

	return v;
}

template<class T>
void IO::PrintList(std::ostream& os, const std::vector<std::unique_ptr<T>>& list){
	size_t N = list.size();
	if (N == 0){
		os << IO::LIST_START << ' ' << IO::LIST_END << ' ';
		return;
	}

	os << IO::LIST_START << ' ';
	for(size_t i = 0; i < N - 1; ++i){
		os << list[i]->Save() << ' ' << IO::LIST_SEP << ' ';
	}
	os << list[N - 1]->Save() << ' ';
	os << IO::LIST_END << ' ';
}
}