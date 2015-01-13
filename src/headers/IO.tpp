namespace Lab3{


//----------------------------------------------
// Factory
//----------------------------------------------

template<class T>
IO::FactoryRegistration<T>::FactoryRegistration(const std::string& s) {
	(*GetMap())[s] = &CreateInstance<T>;
}

template<class T>
T* IO::Factory::CreateInstance(){
	return new T;
}

//----------------------------------------------
// IO
//----------------------------------------------

template<class T>
std::unique_ptr<T> IO::ParseObject(std::istream& is){
	pr("Parsing object of type :" << typeid(T).name());
	std::stringstream ss;
	ss << ReadObject(is);
	std::string type;
	if(!(ss >> type)){
		std::string error = "Failed to read type of object type ";
		error.append(typeid(T).name());
		throw std::invalid_argument(error);
	}
	Utils::Trim(type);
	T* instance = dynamic_cast<T*>(IO::Factory::CreateInstance(type));
	if(!instance){
		std::string error = "Can't cast " + type;
		throw std::invalid_argument(error);
	}
	std::unique_ptr<T> ptr(instance);
	std::string name;
	if(!(ss >> name)){
		std::string error = "Failed to parse name of object of type ";
		error.append(typeid(T).name());
		throw std::invalid_argument(error);
	}
	Utils::Trim(name);
	ptr->SetName(name);	
	ptr->_description = IO::ReadDescription(ss);


	if(!(ss >> *ptr)){
		std::string error = "Failed to parse object of type ";
		error.append(typeid(T).name());
		throw std::invalid_argument(error);
	}
	return ptr;
}

template<class T> 
T IO::ParseStruct(std::istream& is){
	pr("Parsing struct of type :" << typeid(T).name());
	std::stringstream ss;
	ss << ReadObject(is);
	std::string type;
	if(!(ss >> type)){
		std::string error = "Failed to read type of object type ";
		error.append(typeid(T).name());
		throw std::invalid_argument(error);
	}
	Utils::Trim(type);
	T* instance = dynamic_cast<T*>(IO::Factory::CreateInstance(type));
	if(!instance){
		std::string error = "Can't cast " + type;
		throw std::invalid_argument(error);
	}

	if(!(ss >> *instance)){
		std::string error = "Failed to parse object of type ";
		error.append(typeid(T).name());
		throw std::invalid_argument(error);
	}
	T obj = *instance; // copy
	delete instance;
	return obj;	
}

template<class T>
std::vector<std::unique_ptr<T>> IO::ParseList(std::istream& is){
	pr("Parsing list of type :" << typeid(T).name());
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
void IO::PrintList(std::ostream& os, const std::vector<T>& list){
	size_t N = list.size();
	if (N == 0){
		os << IO::LIST_START << ' ' << IO::LIST_END << ' ';
		return;
	}

	os << IO::LIST_START << ' ';
	for(size_t i = 0; i < N - 1; ++i){
		os << Utils::Ptr(list[i])->Save() << ' ' << IO::LIST_SEP << ' ';
	}
	os << Utils::Ptr(list[N - 1])->Save() << ' ';
	os << IO::LIST_END << ' ';
}
}