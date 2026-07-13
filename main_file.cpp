#include <iostream>

class list {
    private:
        struct NodeSingly { // singly linked list
            std::string taskName, taskDesc;
            int priority; // ranging from 1 to 10
            int dateMade[3], dateCompleted[3]; // 0 = Day, 1 = Month, 2 = Year
        };
        NodeSingly *head = nullptr;
    public:
};


int main() {


    return 0;
}
