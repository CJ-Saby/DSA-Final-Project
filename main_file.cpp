#include <iostream>

class list {
    private:

        struct NodeSingly { // task node blueprint
            std::string taskName, taskDesc;
            int priority; // ranging from 1 to 10 with 10 being the highest priority
            int dateMade[3], dateCompleted[3]; // legend of indices: 0 = Day, 1 = Month, 2 = Year
        };
        NodeSingly *head = nullptr;

    public:

        void add_task(std::string taskName, std::string taskDesc, int priority) {
            NodeSingly* newNode = new NodeSingly();
            newNode->taskName = taskName;
            newNode->taskDesc = taskDesc;
            newNode->priority = priority;

            if (head == nullptr) {
                head = newNode;
                return;
            }

            NodeSingly* traverse = head;
            while (traverse->next != nullptr) {

            }
        }

};


int main() {


    return 0;
}
