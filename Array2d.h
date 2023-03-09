#pragma once
template <typename T>
class Array2d {
private:
	int _rows;
	int _columns;
	int* array;
public:
	Array2d() : _rows(0), _columns(0), array(nullptr) {
	}
	Array2d(int size) : _rows(size), _columns(size), array(new T[size * size]) {
	}
	~Array2d() {
		delete[] array;
	}
	T& operator()(int row, int column) {
		return array[(row * _columns) + column];
	}

	void resize(int newSize) {
		erase();
		_columns = newSize;
		_rows = newSize;
		array = new T[newSize * newSize];
	}

	void resize(int newRows, int newColumns) {
		erase();
		_columns = newColumns;
		_rows = newRows;
		array = new T[_columns * _rows];
	}

	void fill(T a) {
		for (int i = 0; i < _columns * _rows; i++) {
			array[i] = a;
		}
	}

	void erase() {
		if (!isEmpty()) {
			delete[] array;
			array = nullptr;
			_rows = 0;
			_columns = 0;
		}
	}

	bool isEmpty() {
		if (array == nullptr)
			return true;
		return false;
	}

	int rows() {
		return _rows;
	}
	int columns() {
		return _columns;
	}
};
