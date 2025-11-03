#include <iostream>

int main() {
    int p[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    std::cout << "d. Value of *p: " << *p << "\n";

    std::cout << "e. Value of p[0]: " << p[0] << "\n";

    std::cout << "f. Value of p[3]: " << p[3] << "\n";

    std::cout << "g. Value of *(p+5): " << *(p+5) << "\n";

    std::cout << "h. Value of *p+5: " << *p+5 << "\n";

    int *q = p - 1;

    std::cout << "j. Value of q[0] (*(p-1)): " << q[0] << "\n";

    std::cout << "k. Value of *(q+10): " << *(q+10) << "\n";

    std::cout << "l. Value of *(q+11) (*(p+10)): " << *(q+11) << "\n";

    return 0;
}

