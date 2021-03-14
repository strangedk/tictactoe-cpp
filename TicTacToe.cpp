#include <iostream>

using namespace std;

class Cell {
public:
	static const short EMPTY_VALUE = -1;

	Cell() : m_value(EMPTY_VALUE) { }

	void Print() const {
		cout << ((GetValue() == -1) ? "*" : (GetValue() ? "X" : "0"));
	}

	short GetValue() const {
		return m_value;
	}

	void SetValue(short value) {
		this->m_value = value;
	}
private:
	short m_value;
};

class Cells {
public:
	static const uint8_t SIZE = 9;
	static const uint8_t SIDE = 3;

	Cells() {
		for (short i = 0; i < SIZE; ++i) {
			m_cells[i] = new Cell();
		}
	}

	~Cells() {
		// TODO: Ask, why it was crashed here?
		//for (short i = 0; i < SIZE; ++i)
			//delete m_cells[i];
		// delete[] m_cells;
	}

	bool SetCell(short id, short value) const {
		if (id >= 0 && id < SIZE) {
			if (m_cells[id]->GetValue() == Cell::EMPTY_VALUE) {
				m_cells[id]->SetValue(value);
				return true;
			}
			else {
				cout << "Cell isn't empty. Choose another one\n";
				return false;
			}
		}
		else {
			cout << "Selected position is outside the game field!\n";
			return false;
		}
	}

	void Print() const {
		for (short i = 0; i < SIZE; ++i) {
			if (!(i % SIDE)) {
				cout << endl;
			}

			m_cells[i]->Print();
		}
		cout << endl;
	}

	bool isWin() {
		const short combinationsQuantity = 8;
		const short winIndexes[combinationsQuantity][SIDE] = {
			{0,1,2}, {3,4,5}, {6,7,8},
			{0,3,6}, {1,4,7}, {2,5,8},
			{0,4,8}, {2,4,6},
		};

		for (short i = 0; i < combinationsQuantity; ++i) {
			for (short j = 0; j < SIDE; ++j) {
				short index = winIndexes[i][j];
				short value = m_cells[index]->GetValue();

				if (value == Cell::EMPTY_VALUE)
					break;
				else if (j > 0) {
					short prevIndex = winIndexes[i][j - 1];
					short prevValue = m_cells[prevIndex]->GetValue();

					if (value != prevValue)
						break;

					if (j == SIDE - 1 && value == prevValue) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool isFull() {
		short filled = 0;

		for (short i = 0; i < SIZE; ++i)
			filled += (m_cells[i]->GetValue() != Cell::EMPTY_VALUE) ? 1 : 0;

		return filled == SIZE;
	}

private:
	Cell* m_cells[SIZE] = {};
};

class Game {
public:
	Game() {
		Cells cells;
		Process(cells);
	}

	void Process(Cells cells) {
		short pos;
		short player = 0;

		while (!cells.isWin() && !cells.isFull()) {
			cells.Print();
			cout << "player [" << (player ? "X" : "0") << "] Enter pos: ";
			cin >> pos;

			if (cells.SetCell(pos, player))
				player = player == 1 ? 0 : 1;
		}

		if (cells.isWin())
			cout << "Result: Player " << (player ? "0" : "X") << " wins!\n";
		else
			cout << "Result: Draw!";

		cells.Print();
	}
};

int main() {
	Game game;
};