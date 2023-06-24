#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class person {
public:
	person() {}
	person(const string& name, int age, const string& address)
		: m_name(name), m_age(age), m_address(address) {}

	void writeToFile(const string& filename) const {
		ofstream file(filename, ios::out | ios::binary);
		if (!file.is_open()) {
			cerr << "Failed to open file for writing: " << filename << endl;
			return;
		}
		file.write(reinterpret_cast<const char*>(&m_age), sizeof(m_age));
		writeStringToFile(file, m_name);
		writeStringToFile(file, m_address);
		file.close();
	}

	void readFromFile(const string& filename) {
		ifstream file(filename, ios::in | ios::binary);
		if (!file.is_open()) {
			cerr << "Failed to open file for reading: " << filename << endl;
			return;
		}
		file.read(reinterpret_cast<char*>(&m_age), sizeof(m_age));
		m_name = readStringFromFile(file);
		m_address = readStringFromFile(file);
		file.close();
	}

	void print() const {
		cout << "Name: " << m_name << endl;
		cout << "Age: " << m_age << endl;
		cout << "Address: " << m_address << endl;
	}

private:
	string m_name;
	int m_age;
	string m_address;

	void writeStringToFile(ofstream& file, const string& str) const {
		size_t size = str.size();
		file.write(reinterpret_cast<const char*>(&size), sizeof(size));
		file.write(str.c_str(), size);
	}

	string readStringFromFile(ifstream& file) {
		size_t size;
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		string str(size, '\0');
		file.read(&str[0], size);
		return str;
	}
};

int main() {
	person person1("Denis Dzyuba", 17, "Pererva");
	person1.writeToFile("person.bin");

	person person2;
	person2.readFromFile("person.bin");
	person2.print();

	return 0;
}