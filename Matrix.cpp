#include "Matrix.h";

bool isDigits(string str) {
    return str.find_first_not_of("0123456789") == string::npos;
}

bool isBinary(string str) {
    return str.find_first_not_of("01") == string::npos;
}

Matrix::Matrix(int inRow, int inCol) {
	row = inRow;
	col = inCol;
}

//vector<vector<int>> Matrix::getMatrix() {
//
//}
//
//void Matrix::setMatrix(vector<vector<int>>) {
//
//}
//
int Matrix::getRow() {
    return row;
}

void Matrix::setRow(vector<int> inRow) {
    data.push_back(inRow);
}

int Matrix::getCol() {
    return col;
}
//
void Matrix::setCol(int inCol) {
    col = inCol;
}
//
int Matrix::getValue(int inRow, int inCol) {
    return data.at(inRow).at(inCol);
}
//
void Matrix::setValue(int inRow, int inCol, int value) {
    data.at(inRow).at(inCol) = value;
}

bool Matrix::loadMatrix(string str, ofstream& out) {
    int tempValue, total = 0;
    string rowInp, colInp, tempInp;
    vector<int> currRow;       //this vector represents a row in the 2-D vector
    stringstream ss(str);     //take the input line & create a string stream

    ss >> rowInp >> colInp;
    if (isDigits(rowInp)) {
        row = stoi(rowInp);
        if (row < 1 || row > 5) {
            out << "Row value is out of range" << endl;
            return false;
        }
    }
    else {
        out << "Row input value is not valid" << endl;
        return false;
    }
    if (isDigits(colInp)) {
        col = stoi(colInp);
        if (col < 1 || col > 5) {
            out << "Column value is out of range" << endl;
            return false;
        }
    }
    else {
        out << "Column input value is not valid" << endl;
        return false;
    }
    //this loop code taken from class notes
    for (int i = 0; i < row; ++i) {
        currRow.clear();

        for (int j = 0; j < col; ++j) {
            if (ss >> tempInp) {
                if (!(isBinary(tempInp))) {
                    out << "Vector value is not 0 or 1" << endl;
                    return false;
                }
                tempValue = stoi(tempInp);
                currRow.push_back(tempValue);
                total++;
            }
            else {
                out << "There is not enough input for this matrix" << endl;
                return false;
            }
        }
        setRow(currRow);
    }
    if (total != (row * col)) {
        out << "There is not enough input for this matrix" << endl;
        return false;
    }
    return true;
}

void Matrix::printMatrix() {
    for (int i = 0; i < data.size(); i++) {
        cout << '\t';
        for (int j = 0; j < data.at(i).size(); j++) {
            cout << data.at(i).at(j) << " ";
        }
        cout << endl;
    }
}

void Matrix::showDetails(ofstream& out) {
    int diagcount = 0;
    bool isSym = true;
    out << "Reflexive, symmetric, or transitive properties: ";
    if (data.at(0).size() != data.size()) {
        out << "Matrix must be square" << endl;
    }
    else {
        for (int i = 0; i < data.size(); i++) {
            if (data.at(i).at(i) == 1) {
                diagcount++;
            }
        }
        if (diagcount == data.size()) {
            out << "The matrix is reflexive.";
        }
        // loop code from chat gpt
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data.size(); j++) {
                if (data.at(i).at(j) != data.at(j).at(i))
                    isSym = false;
            }
        }
        if (isSym)
            out << " The matrix is symmetric.";
    }
}
Matrix Matrix::operator*(Matrix& rhs) {
    vector<int> row;
    int temp;
    Matrix multMat = Matrix(getRow(), rhs.getCol());
    for (int i = 0; i < getRow(); ++i) {
        row.clear();
        for (int j = 0; j < rhs.getRow(); ++j) {
            row.push_back(0);
        }
        multMat.setRow(row);
    }

    // loop code from chat gpt
    for (int i = 0; i < getRow(); ++i) {
        for (int j = 0; j < rhs.getCol(); ++j) {
            for (int k = 0; k < getCol(); ++k) {
                multMat.setValue(i, j, getValue(i, k) * rhs.getValue(k, j) + multMat.getValue(i, j));
            }
        }
    }
    return multMat;
}

Matrix Matrix::operator+(Matrix rhs) {
    vector<int> row;
    Matrix sumMat = Matrix(getRow(), getCol());
    for (int i = 0; i < getRow(); i++) {
        row.clear();
        for (int j = 0; j < getCol(); j++) {
            row.push_back(getValue(i, j) + rhs.getValue(i, j));
        }
        sumMat.setRow(row);
    }
    return sumMat;
}

//Matrix Matrix::operator=(Matrix& rhs) {
//
//}

Matrix Matrix::operator-(Matrix& rhs) {
    vector<int> row;
    Matrix diffMat = Matrix(getRow(), getCol());
    for (int i = 0; i < getRow(); i++) {
        row.clear();
        for (int j = 0; j < getCol(); j++) {
            row.push_back(getValue(i, j) - rhs.getValue(i, j));
        }
        diffMat.setRow(row);
    }
    return diffMat;
}

ofstream& operator<<(ofstream& out, Matrix& rhs) {
    for (int i = 0; i < rhs.getRow(); i++) {
        out << '\t';
        for (int j = 0; j < rhs.getCol(); j++) {
            out << setw(3) << rhs.getValue(i, j);
        }
        out << endl;
    }
    return out;
}