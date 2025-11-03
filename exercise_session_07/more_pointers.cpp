#include <iostream>

const int ROWS = 2;
const int COLS = 5;

int** swap_and_reverse_rows(int** M) {
    int** M2 = new int*[ROWS];
    
    M2[0] = new int[COLS];
    M2[1] = new int[COLS];


    for (int i = 0; i < COLS; ++i) {
        *(*(M2) + i) = *(*(M + 1) + (COLS - 1 - i));
    }

    for (int i = 0; i < COLS; ++i) {
        *(*(M2 + 1) + i) = *(*M + (COLS - 1 - i));
    }

    return M2;
}


void print_array(int** arr) {
    for (int i = 0; i < ROWS; ++i) {
        std::cout << "Row " << i << ": [ ";
        for (int j = 0; j < COLS; ++j) {
            std::cout << *(*(arr + i) + j) << (j < COLS - 1 ? ", " : "");
        }
        std::cout << " ]\n";
    }
}

void cleanup(int** arr) {
    delete[] *arr;      // delete[] M[0]
    delete[] *(arr + 1);  // delete[] M[1]
    
    delete[] arr;
}


int main() {
    std::cout << "--- 2D Array Pointer Manipulation ---\n";

    int ** M = new int *[ROWS];
    M [0] = new int [COLS]{0 ,1 ,2 ,3 ,4};
    M [1] = new int [COLS]{5 ,6 ,7 ,8 ,9};

    std::cout << "\nOriginal Array M:\n";
    print_array(M);

    int** M2 = swap_and_reverse_rows(M);

    std::cout << "\nResult Array M2 (Swapped and Reversed):\n";
    print_array(M2);


    cleanup(M);
    cleanup(M2);

    std::cout << "\nCleanup successful.\n";

    return 0;
}

