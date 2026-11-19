
#include "LinkedList.h"

#include <iostream>
#include <vector>
#include <cstdlib>

int main() {
    std::srand(1234);

    LinkedList<int> list;
    std::vector<int> model;

    bool ok = true;

    for (int step = 0; step < 5000 && ok; step++) {
        int op = std::rand() % 9;
        int v = std::rand() % 5;
        unsigned int n = model.size();

        switch (op) {
        case 0:
            list.AddHead(v);
            model.insert(model.begin(), v);
            break;

        case 1:
            list.AddTail(v);
            model.push_back(v);
            break;

        case 2:
            if (n > 0) {
                list.RemoveHead();
                model.erase(model.begin());
            }
            break;

        case 3:
            if (n > 0) {
                list.RemoveTail();
                model.pop_back();
            }
            break;

        case 4: {
            unsigned int i = std::rand() % (n + 1);
            list.InsertAt(v, i);
            model.insert(model.begin() + i, v);
            break;
        }

        case 5:
            if (n > 0) {
                unsigned int i = std::rand() % n;
                list.RemoveAt(i);
                model.erase(model.begin() + i);
            }
            break;

        case 6: {
            unsigned int removed = list.Remove(v);
            unsigned int expect = 0;

            for (std::size_t i = model.size(); i > 0; i--) {
                if (model[i - 1] == v) {
                    model.erase(model.begin() + (i - 1));
                    expect++;
                }
            }

            if (removed != expect) {
                ok = false;
            }
            break;
        }

        case 7: {
            LinkedList<int> copy(list);

            if (!(copy == list)) {
                ok = false;
            }
            break;
        }

        case 8: {
            LinkedList<int> other;
            other = list;

            if (!(other == list)) {
                ok = false;
            }
            break;
        }
        }

        // Check linked list invariants and size.
        if (!list.IsConsistent() || list.NodeCount() != model.size()) {
            ok = false;
        }

        // Compare every element.
        for (unsigned int i = 0; ok && i < model.size(); i++) {
            if (list[i] != model[i]) {
                ok = false;
            }
        }

        if (!ok) {
            std::cout << "MISMATCH at step " << step
                      << " (op " << op << ")" << std::endl;
        }
    }

    if (ok) {
        std::cout << "all 5000 random operations agree" << std::endl;
    }

    return 0;
}
