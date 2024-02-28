#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j);
void Input(int** a, const int rowCount, const int colCount, int i, int j);
void Print(int** a, const int rowCount, const int colCount, int i, int j);
int Part1_Count(int** a, const int rowCount, const int colCount, int j, int result);
void Part2_SortByPositivePairsSum(int** a, const int rowCount, const int colCount, int i, int j);
unsigned int SumPositiveEvenElements(int* row, const int colCount, int j, unsigned int sum);
void SwapRows(int** a, int row1, int row2, const int colCount, int j);

int main() {
    srand((unsigned)time(NULL));
    int Low = -17;
    int High = 15;
    int rowCount, colCount;
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    if (rowCount <= 0 || colCount <= 0) {
        cout << "Incorrect matrix dimensions!" << endl;
        return 1;
    }

    int** a = new int* [rowCount];
    Create(a, rowCount, colCount, Low, High, 0, 0);

    Print(a, rowCount, colCount, 0, 0);
    int count = Part1_Count(a, rowCount, colCount, 0, 0);
    cout << "Number of columns without zero elements: " << count << endl;
    cout << endl;
    Part2_SortByPositivePairsSum(a, rowCount, colCount, 0, 0);
    cout << "Matrix after sorting by sum of positive even elements in rows:" << endl;
    Print(a, rowCount, colCount, 0, 0);
    cout << endl;

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j) {
    if (i < rowCount) {
        if (j < colCount) {
            a[i] = new int[colCount];
            a[i][j] = Low + rand() % (High - Low + 1);
            Create(a, rowCount, colCount, Low, High, i, j + 1);
        }
        else {
            Create(a, rowCount, colCount, Low, High, i + 1, 0);
        }
    }
}

void Input(int** a, const int rowCount, const int colCount, int i, int j) {
    if (i < rowCount) {
        if (j < colCount) {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
            Input(a, rowCount, colCount, i, j + 1);
        }
        else {
            Input(a, rowCount, colCount, i + 1, 0);
        }
    }
}

void Print(int** a, const int rowCount, const int colCount, int i, int j) {
    if (i < rowCount) {
        if (j < colCount) {
            cout << setw(4) << a[i][j];
            Print(a, rowCount, colCount, i, j + 1);
        }
        else {
            cout << endl;
            Print(a, rowCount, colCount, i + 1, 0);
        }
    }
}

int Part1_Count(int** a, const int rowCount, const int colCount, int j, int result) {
    if (j < colCount) {
        bool hasZero = false;
        int i = 0;
        while (!hasZero && i < rowCount) {
            if (a[i][j] == 0) {
                hasZero = true;
            }
            i++;
        }
        if (!hasZero) {
            result++;
        }
        return Part1_Count(a, rowCount, colCount, j + 1, result);
    }
    return result;
}

unsigned int SumPositiveEvenElements(int* row, const int colCount, int j, unsigned int sum) {
    if (j < colCount) {
        if (row[j] > 0 && row[j] % 2 == 0)
            sum += row[j];
        return SumPositiveEvenElements(row, colCount, j + 1, sum);
    }
    return sum;
}

void SwapRows(int** a, int row1, int row2, const int colCount, int j) {
    if (j < colCount) {
        swap(a[row1][j], a[row2][j]);
        SwapRows(a, row1, row2, colCount, j + 1);
    }
}

void Part2_SortByPositivePairsSum(int** a, const int rowCount, const int colCount, int i, int j) {
    if (i < rowCount - 1) {
        if (j < rowCount - i - 1) {
            if (SumPositiveEvenElements(a[j], colCount, 0, 0) > SumPositiveEvenElements(a[j + 1], colCount, 0, 0))
                SwapRows(a, j, j + 1, colCount, 0);
            Part2_SortByPositivePairsSum(a, rowCount, colCount, i, j + 1);
        }
        Part2_SortByPositivePairsSum(a, rowCount, colCount, i + 1, 0);
    }
}
