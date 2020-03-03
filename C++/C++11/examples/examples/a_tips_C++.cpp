// ostream based object content printings
	friend ostream& operator<< (ostream& os, const User& obj)
	{
		return os << "first name: " << obj.first_name << " last name: " << obj.last_name;
	}