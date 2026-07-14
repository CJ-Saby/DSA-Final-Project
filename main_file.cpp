#include <iostream>

class list {
    private:

        struct patientCase { // task node blueprint
            std::string patientName, caseDesc; // caseDesc is the description of the patient's case
            int priority; // legend: 1 = non emergency, 2 = emergency, 3 = highly urgent emergency
            int dateMade[3], dateCompleted[3]; // legend of indices: 0 = Day, 1 = Month, 2 = Year
        };
        typedef patientCase* NodePtr;
        patientCase *head = nullptr;

    public:

        void view_task_details (std::string patientName){

            // WIP

        }

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
