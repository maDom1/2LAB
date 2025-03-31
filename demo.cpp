#include <iostream>
#include "Queap.h"

using namespace my_project;
using namespace std;

int main() {
    try {
        Queap queaps[3];

        queaps[0].enqueue(5);
        queaps[0].printQueap();

        queaps[0].dequeue();
        queaps[0].printQueap();

        queaps[0].enqueue(8);
        queaps[0].printQueap();

        queaps[0].enqueue(11);
        queaps[0].printQueap();

        queaps[0].enqueue(-13);
        queaps[0].printQueap();

        queaps[0].enqueue(15);
        queaps[0].printQueap();

        cout << "Min value: " << queaps[0].findMin() << '\n';
        cout << "Size: " << queaps[0].size() << '\n';
        cout << "Is empty: " << (queaps[0].isEmpty() ? "Yes" : "No") << '\n';

        queaps[0].enqueue(15); // should throw DuplicateValueException
    }
    catch (const DuplicateValueException& e) {
        cerr << e.what() << '\n';
    }
    return 0;
}
