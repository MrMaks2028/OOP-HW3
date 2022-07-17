#include <iostream>
#include <vector>
class DynamicArray {
public:
	DynamicArray() {}
	DynamicArray(const DynamicArray& other) {
		_size = other._size;
		_capacity = other._capacity;
		delete[] _data;
		_data = new int[_capacity];
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

	int& at(int pos) {
		return _data[pos];
	}
	const int& at(int pos)const {
		return _data[pos];
	}
	int& operator[] (int i) {
		return _data[i];
	}
	const int& operator[](int i)const {
		return _data[i];
	}
	int& front() {
		return _data[0];
	}
	const int& front()const {
		return _data[0];
	}
	int& back() {
		return _data[_size - 1];
	}
	const int& back()const {
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
		_data = new int[_capacity + capacity];
		for (int i = 0; i < _size; i++)
			_data[i] = tmp[i];
		delete[] tmp;
		_capacity += capacity;
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
		_data = nullptr;
		_size = 0;
	}
	void insert(int pos, int value) {
		if(_size + 1 > _capacity){
			_size++;
			int* tmp = new int[_size];
			for (int i = 0; i < pos; i++) {
				tmp[i] = _data[i];
			}
			tmp[pos] = value;
			for (int i = pos+1; i < _size; i++) {
				tmp[i] = _data[i-1];
			}
			delete[] _data;
			_data = new int[_size];
			for (int i = 0; i < _size; i++) {
				_data[i] = tmp[i];
			}
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
			for (int i = pos + 1; i < _size; i++) {
				tmp[i] = _data[i - 1];
			}
			delete[] _data;
			_data = new int[_size];
			for (int i = 0; i < _size; i++) {
				_data[i] = tmp[i];
			}
			delete[] tmp;
		}
	}
	void insert(int pos, int count, int value){
		if (_size + count > _capacity) {
			_size += count;
			int k = 0;
			int* tmp = new int[_size];
			for (int i = 0; i < pos; i++) {
				tmp[i] = _data[i];
				k++;
			}
			for (int i = pos; i < _size - k; i++) {
				tmp[i] = value;
			}
			for (int i = pos + count; i < _size; i++) {
				tmp[i] = _data[i - count];
			}
			delete[] _data;
			_data = new int[_size];
			for (int i = 0; i < _size; i++) {
				_data[i] = tmp[i];
			}
			delete[] tmp;
			_capacity = _size;
		}
		if (_size + count <= _capacity) {
			_size += count;
			int k = 0;
			int* tmp = new int[_size];
			for (int i = 0; i < pos; i++) {
				tmp[i] = _data[i];
				k++;
			}
			for (int i = pos; i < _size - k; i++) {
				tmp[i] = value;
			}
			for (int i = pos + count + 1; i < _size; i++) {
				tmp[i] = _data[i - count];
			}
			delete[] _data;
			_data = new int[_size];
			for (int i = 0; i < _size; i++) {
				_data[i] = tmp[i];
			}
			delete[] tmp;
		}
	}
	void erase(int pos) {
		int count = 0;
		int* tmp = new int[_size];
		for (int i = 0; i < _size; i++) {
			tmp[i] = _data[i];
		}
		delete[] _data;
		_data = new int[_size - 1];
		for (int i = 0; i < pos; i++)
			_data[i] = tmp[i];
		for(int i = pos; i < _size - 1; i++)
			_data[i] = tmp[i + 1];
		_size--;
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
		std::cout << "[";
		for (int i = 0; i < _size; i++)
			std::cout << _data[i] << ", ";
		std::cout << "\b\b]";
	}

	DynamicArray operator= (const DynamicArray& other){
		_size = other._size;
		_capacity = other._capacity;
		delete[] _data;
		_data = new int[_capacity];
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
	using namespace std;

	DynamicArray a(5, new int[5]{ 1,2,3,4,5 });
	DynamicArray b(10); 
	b[0] = 10; b[1] = 20; 
	b[2] = 30; b[3] = 40; 
	b[4] = 50; b[5] = 60; 
	b[6] = 70; b[7] = 80; 
	b[8] = 90; b[9] = 100;
	DynamicArray c = a;
	DynamicArray d; d.reserve(20);
	DynamicArray f(6, new int[6]{ 2,4,6,8,10,12 });
	DynamicArray x(4, new int[4]{ 12,16,22,26 });
	DynamicArray y;

	cout << "at:  " << a.at(0) << " " << a.at(1) << " " << a.at(2) << " " << a.at(3) << " " << a.at(4) << " ";
	cout << "\n\noperator []:  " << c[0] << " " << c[1] << " " << c[2] << " " << c[3] << " " << c[4] << " ";
	cout << "\n\nfront:  " << a.front();
	cout << "\n\nback:  " << c.back();
	cout << "\n\ndata:  " << b.data();
	cout << "\n\nempty:  " << "\"d\" " << d.empty() << " \"a\" " << a.empty();
	cout << "\n\nsize:  " << "\"c\" " << c.size() << " \"d\" " << d.size();
	cout << "\n\ncapacity:  " << "\"a\" " << a.capacity() << " \"b\" " << b.capacity();
	cout << "\n\nreserve:  " << "\"a\" capacity Before reserve: " << a.capacity(); 
	a.reserve(10);
	cout << "\t\"a\" capacity After reserve: " << a.capacity();
	cout << "\n\nshrink_to_fit:  " << "\"a\" capacity Before shrink_to_fit: " << a.capacity();
	a.shrink_to_fit();
	cout << "\t\"a\" capacity After shrink_to_fit: " << a.capacity();
	cout << "\n\nclear:  " << "\"f\" Before clear:  size -> " << f.size() << "  "; f.showArr();
	f.clear();
	cout << "\t\"f\" After clear:  size -> " << f.size() << "  "; f.showArr();
	cout << "\n\ninsert(pos, value):  " << "\"a\" Before insert: "; a.showArr();
	a.insert(4, 100);
	cout << "\t\"a\" After insert: "; a.showArr();
	cout << "\n\nerase(pos):  " << "\"a\" Before erase: "; a.showArr();
	a.erase(4);
 	cout << "\t\"a\" After erase: "; a.showArr();
	cout << "\n\ninsert(pos, count, value):  " << "\"b\" Before insert: "; b.showArr();
	b.insert(5, 10, 200);
	cout << "\t\"b\" After insert: "; b.showArr();
	cout << "\n\nerase(first, last):  " << "\"b\" Before erase: "; b.showArr();
	b.erase(5, 14);
	cout << "\t\"b\" After erase: "; b.showArr();
	cout << "\n\npush_back:  " << "\"d\" Before push_back: "; d.showArr();
	d.push_back(1); d.push_back(2); d.push_back(3); d.push_back(4); d.push_back(5);
	cout << "\t\"d\" After push_back: "; d.showArr();
	cout << "\n\nemplace_back:  " << "\"d\" Before emplace_back: "; d.showArr();
	d.emplace_back(6); d.emplace_back(7); d.emplace_back(8); d.emplace_back(9); d.emplace_back(10);
	cout << "\t\"d\" After push_back: "; d.showArr();
	cout << "\n\npop_back:  " << "\"d\" Before pop_back: "; d.showArr();
	d.pop_back(); d.pop_back(); d.pop_back(); d.pop_back(); d.pop_back();
	cout << "\t\"d\" After push_back: "; d.showArr();
	cout << "\n\nresize:  " << "\"c\" Before resize: "; c.showArr();
	c.resize(10);
	cout << "\t\"c\" After resize: "; c.showArr();
	cout << "\n\nswap:  " << "Before swap: \"a\" = "; a.showArr();
	cout << "\t\"b\" = "; b.showArr();
	a.swap(b);
	cout << "\nAfter swap: \"a\" = "; a.showArr();
	cout << "\t\"b\" = "; b.showArr();
	cout << "\n\nMove semantics: "; 
	cout << "  Before move \"x\" = "; x.showArr(); cout << "\t \"y\" = "; y.showArr();
	y = move(x);
	cout << "\n\nAfter move \"x\" = "; x.showArr(); cout << "\t \"y\" = "; y.showArr();

	return 0;
}