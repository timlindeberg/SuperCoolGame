namespace Lab3{

template<class T>
GameStream& GameStream::operator<<(const T& t){
	_ss << t;
	return *this;
}

}
