#include <iostream>
#include <vector>
using namespace std;

class DynamicArray {
public:
	DynamicArray() {}
	DynamicArray(const DynamicArray& other) {
		_size = other._size;
		_capacity = other._capacity;
		_data = new int[other._capacity];
		for (int i = 0; i < _size; i++)
			_data[i] = other._data[i];
	}
	DynamicArray(DynamicArray&& other) {
			_data = other._data;
			_size = other._size;
			_capacity = other._capacity;
			other._data = nullptr;
			other._size = other._capacity = 0;
	}
	DynamicArray(int size) {
		_size = size;
		_capacity = _size;
		if (_capacity != 0)
			_data = new int[_size];
		else
			_data = 0;
	}
	DynamicArray(int size, int* data) {
		_size = size;
		_capacity = _size;
		if (_size != 0){
			_data = new int[_size];
			for (int i = 0; i < _size; i++)
				_data[i] = data[i];
			}
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
	void reserve(int capacity) {
		int* tmp = new int[_size];
		for (int i = 0; i < _size; i++)
			tmp[i] = _data[i];
		delete[] _data;
		_data = new int[capacity];
		for (int i = 0; i < _size; i++)
			_data[i] = tmp[i];
		delete[] tmp;
		_capacity = capacity;
	}
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
	void insert(int pos, int value) {
		if(_size + 1 > _capacity){
			_size++;
			int* tmp = new int[_size];
			for (int i = 0; i < pos; i++) {
				tmp[i] = _data[i];
			}
			tmp[pos--] = value;
			for (int i = pos+2; i < _size; i++) {
				tmp[i] = _data[i];
			}
			delete[] _data;
			
			_data = new int[_size];
			for (int i = 0; i < _size; i++)
				_data[i] = tmp[i];
			delete[] tmp;
			_capacity = _size;
		}
		if (_size + 1 <= _capacity) {
			_size++;
			int* tmp = new int[_size];
			for (int i = 0; i < pos; i++) {
				tmp[i] = _data[i];
			}
			tmp[pos] = value;
			for (int i = pos++; i < _size; i++) {
				tmp[i] = _data[i];
			}
			delete[] _data;

			_data = new int[_capacity];
			for (int i = 0; i < _size; i++)
				_data[i] = tmp[i];
			delete[] tmp;
		}
	}
	void erase(int pos) {
		int* tmp = new int[_size];
		for (int i = 0; i < _size; i++)
			tmp[i] = _data[i];
		delete[] _data;
		_data = new int[_size - 1];
		for (int i = 0; i < _size - 1; i++){
			if (tmp[i] == pos)
				continue;
			_data[i] = tmp[i];
		}
		_size = _size - 1;
	}
	void erase(int first, int last){ 
		int count = 0;
		int* tmp = new int[_size];
		for (int i = 0; i < _size; i++) {
			tmp[i] = _data[i];
		}
		delete[] _data;
		_data = new int[_size - (last - first)];
		for (int i = 0; i < _size; i++){
			if (i >= first && i <= last){
				count++;
				continue;
			}
			_data[i - count] = tmp[i];
		}
		_size = _size - (last - first + 1);
		/*int* tmp = new int[_size];
		for (int i = 0; i < _size; i++)
			tmp[i] = _data[i];
		delete[] _data;
		_data = new int[_size - (last - first)];
		for (int i = 0; i < _size - (last - first); i++) {
			if (tmp[i] >= first && tmp[i] <= last)
				continue;
			_data[i] = tmp[i];
		}
		_size = _size - (last - first);*/
	}
	void push_back(int value) {
		if(_size + 1 > _capacity){
			int* tmp = new int[_size];
			for (int i = 0; i < _size; i++)
				tmp[i] = _data[i];
			delete[] _data;
			_data = new int[_size + 1];
			for (int i = 0; i < _size; i++)
				_data[i] = tmp[i];
			_data[_size] = value;
			delete[] tmp;
			_size = _size + 1;
			_capacity = _size;
		}
		if (_size + 1 <= _capacity) {
			_data[_size] = value;
			_size = _size + 1;
		}
	}
	void emplace_back(int value) {
		if (_size + 1 > _capacity) {
			int* tmp = new int[_size];
			for (int i = 0; i < _size; i++)
				tmp[i] = _data[i];
			delete[] _data;
			_data = new int[_size + 1];
			for (int i = 0; i < _size; i++)
				_data[i] = tmp[i];
			_data[_size] = value;
			delete[] tmp;
			_size++;
			_capacity = _size;
		}
		if (_size + 1 <= _capacity) {
			_data[_size] = value;
			_size++;
		}
	}
	void pop_back() {
		int* tmp = new int[_size];
		for (int i = 0; i < _size; i++)
			tmp[i] = _data[i];
		delete[] _data;
		_data = new int[_capacity];
		for (int i = 0; i < _size; i++)
			_data[i] = tmp[i];
		delete[] tmp;
		_size--;
	}
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
		}
		if (size = _size)
			size = _size;
	}
	void swap(DynamicArray& other) {
		int *tmp = new int[_size];
		for (int i = 0; i < _size; i++)
			tmp[i] = _data[i];
		delete[] _data;
		_data = new int[other._size];
		for (int i = 0; i < other._size; i++)
			_data[i] = other._data[i];
		delete[] other._data;
		other._data = new int[_size];
		for (int i = 0; i < _size; i++)
			other._data[i] = tmp[i];
		delete[] tmp;
		int tmp2 = _size;
		_size = other._size;
		other._size = tmp2;

	}
	void showArr() {
		cout << "[";
		for (int i = 0; i < _size; i++)
			cout << _data[i] << ", ";
		cout << "\b\b]";
	}

	DynamicArray operator= (const DynamicArray& other)
	{
		_size = other._size;
		_capacity = other._capacity;
		_data = new int[other._capacity];
		for (int i = 0; i < _size; i++)
			_data[i] = other._data[i];

		return *this;
	}
	DynamicArray operator= (DynamicArray&& other) {
		_data = other._data;
		_size = other._size;
		_capacity = other._capacity;
		other._data = nullptr;
		other._size = other._capacity = 0;

		return *this;
	}

private:
	int _size = 0;
	int _capacity = 0;
	int* _data = nullptr;
};

int main() {
	setlocale(LC_ALL, "Russian");

	/*DynamicArray arr1(5, new int[5]{ 1,2,3,4,5 });
	DynamicArray arr2(arr1);
	DynamicArray arr3(5, new int[5]{ 6,7,8,9,10 });
	cout << "at: " << arr1.at(0) << endl;
	cout << "at: " << arr2.at(0) << endl;
	cout << "Arr1 Size: " << arr1.size() << " Arr1 Capacity: " << arr1.capacity() << endl;
	cout << "Arr2 Size: " << arr2.size() << " Arr2 Capacity: " << arr2.capacity() << endl;*/

	DynamicArray ar(5, new int[5]{1,2,3,4,5});
	cout << ar.size() << " " << ar.capacity();
	ar.reserve(10);
	cout << "\n\n" << ar.size() << " " << ar.capacity();
	ar.push_back(6);
	cout << "\n\n" << ar.size() << " " << ar.capacity();
	cout << "\n\n";
	ar.showArr();
	ar.pop_back();
	cout << "\n\n" << ar.size() << " " << ar.capacity();
	cout << "\n\n";
	ar.showArr();
	ar.shrink_to_fit();
	ar.insert(2, 10);
	cout << "\n\n" << ar.size() << " " << ar.capacity();
	cout << "\n\n";
	ar.showArr();

	/*vector<int> vec(2);
	vec[0] = 1;
	vec[1] = 2;
	cout << vec.size() << " " << vec.capacity();
	vec.pop_back();
	cout << vec.size() << " " << vec.capacity();
	vec.push_back(2);
	cout << vec.size() << " " << vec.capacity();*/


	return 0;
}