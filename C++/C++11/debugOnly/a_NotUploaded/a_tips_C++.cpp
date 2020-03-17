// ostream based object content printings
	friend ostream& operator<< (ostream& os, const User& obj)
	{
		return os << "first name: " << obj.first_name << " last name: " << obj.last_name;
	}

	int count(0); 
	int count{ 0 }; 

	int array1[]{ 5, 3, 2, 1, 4 };
	int array1[4]{};

	int *m_data;
	assert(length > 0);
	m_data = new int[length];
	delete[] m_data;
	m_data = nullptr;

	int& operator[](int index) {
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}
	intArray[3] = 10;

	for (const auto &x : args) std::cout << x << " "; // range based for loop