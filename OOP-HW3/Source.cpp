#include <iostream>
#include <vector>
using namespace std;

class DynamicArray {
public:
	DynamicArray() {
		_size = 0;
		_capacity = 0;
		_data = nullptr;
	}
	DynamicArray(const DynamicArray& other) {
		if (this != &other) {
			delete[] _data;
			_data = new int[other._capacity];
			for (int i = 0; i < other._size; i++)
				_data[i] = other._data[i];
			_size = other._size;
			_capacity = other._capacity;
		}
	}
	DynamicArray(DynamicArray&& other) {
		if (this != &other) {
			delete[] _data;
			_data = other._data;
			_size = other._size;
			_capacity = other._capacity;
			other._data = nullptr;
			other._size = other._capacity = 0;
		}
	}
	DynamicArray(int size) {
		_size = size;
		_capacity = _size;
		if (_capacity != 0)
			_data = new int[_capacity];
		else
			_data = 0;
	}
	~DynamicArray() {
		if (_data)
			delete[] _data;
	}


	auto at(int pos)->int& {
		return _data[pos];
	}
	auto at(int pos)const->const int& {
		return _data[pos];
	}
	auto operator[] (int i)->int& {
		return _data[i];
	}
	auto operator[](int i)const->const int& {
		return _data[i];
	}
	auto front()->int& {
		return _data[0];
	}
	auto front()const->const int& {
		return _data[0];
	}
	auto back()->int& {
		return _data[_size - 1];
	}
	auto back()const->const int& {
		return _data[_size - 1];
	}
	int* data() {
		return _data;
	}
	bool empty() {
		if (_size > 0) {
			return false;
		}
		else {
			return true;
		}
	}
	int size() const {
		return _size;
	}
	void reserve(int capacity) {}
	int capacity() const {
		return _capacity;
	}
	void shrink_to_fit() {
		int* tmp = new int[_size];
		for (int i = 0; i < _size; i++) {
			tmp[i] = _data[i];
		}
		_capacity = _size;
		delete[]_data;
		_data = new int[_capacity];
		for (int i = 0; i < _capacity; i++) {
			_data[i] = tmp[i];
		}
		delete[]tmp;
	}
	void clear() {
		delete[] _data;
		_size = 0;
	}
	void insert(int pos, int value, int count) {}
	void erase(int first, int last) {}
	void push_back(int value) {
		resize(_size + 1);
		_data[_size - 1] = value;
	}
	void emplace_back(int value) {}
	void pop_back() {}
	void resize(int size, int value = 0) {
		if (size > _size) {
			int* tmp = new int[_size];
			for (int i = 0; i < _size; i++)
				tmp[i] = _data[i];
			delete[] _data;
			_data = new int[size];
			for (int i = 0; i < _size; i++)
				_data[i] = tmp[i];
			for (int i = _size; i < size; i++)
				_data[i] = value;
			delete[] tmp;
			_size = size;
			_capacity = _size;
		}
		if (size < _size) {
			int* tmp = new int[_size];
			for (int i = 0; i < _size; i++)
				tmp[i] = _data[i];
			delete[] _data;
			_data = new int[size];
			for (int i = 0; i < size; i++)
				_data[i] = tmp[i];
			delete[] tmp;
			_size = size;
			_capacity = _size;
		}
		if (size = _size)
			size = _size;
	}
	void swap(DynamicArray& other) {}

	DynamicArray operator= (const DynamicArray& other)
	{
		if (this == &other) {
			return *this;
		}
		delete[] _data;
		_data = new int[other._size];

		_size = other._size;
		_capacity = other._capacity;

		for (int i = 0; i < _size; i++)
			_data[i] = other._data[i];

		return *this;
	}
	DynamicArray operator= (DynamicArray&& other) {}

private:
	int _size;
	int _capacity;
	int* _data;

	int* allocate(int size) {
		int* _data = new int[size];
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	DynamicArray arr(5);
	for (int i = 0; i < arr.capacity(); i++)
		arr[i] = i + 1;
	cout << "Size: " << arr.size() << "\nCapacity: " << arr.capacity() << endl;
	for (int i = 0; i < arr.capacity(); i++)
		cout << arr[i] << ", ";
	cout << "\b\b\n";
	arr.resize(10, 0);
	cout << "\nNew Size: " << arr.size() << "\nNew Capacity: " << arr.capacity() << endl;
	for (int i = 0; i < arr.capacity(); i++)
		cout << arr[i] << ", ";
	cout << "\b\b\n";
	arr.resize(3);
	for (int i = 0; i < arr.capacity(); i++)
		cout << arr[i] << ", ";
	cout << "\b\b\n";
	/*arr.clear();
	cout << "\nNew Size: " << arr.size() << "\nNew Capacity: " << arr.capacity() << endl;*/

	return 0;
}