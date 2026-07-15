#include <iostream>
#include <limits>

class Queue {
    private:

        struct patientCase { // task node blueprint
            std::string patientName, caseDesc; // caseDesc is the description of the patient's case
            std::string patientID; // contains a unique identifier for the patient case
            int priority; // legend: 1 = non emergency, 2 = emergency, 3 = highly urgent emergency
            int dateMade[3], dateCompleted[3]; // legend of indices: 0 = Day, 1 = Month, 2 = Year
            patientCase* next;
        };

        typedef patientCase* NodePtr;

        NodePtr front = nullptr;
        NodePtr rear = nullptr;
        int numItems = 0;
    
    public:

        void sort_queue(NodePtr caseNode) { // REMOVE THIS?
            std::cout << "test";
        }

        void add_record() {
            // initialize variables
            std::string name, desc, id;
            int level;

            // ask the user for inputs
            std::cout << "Enter the patient's name: ";
            std::getline(std::cin, name);
            std::cout << "Enter a description of the patient's case: ";
            std::getline(std::cin, desc);
            std::cout << "Enter the status of the case (1 = non emergency, 2 = emergency, 3 = urgent emergency): ";
            while (true) { // priority level input validation
                if (!(std::cin >> level)) {
                    std::cout << "Input must be an integer, please try again: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }

                if (level < 1 || level > 3) {
                    std::cout << "Level value must be 1, 2, or 3. Please try again: ";
                    continue;
                }

                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // removes any newline in the buffer

            
            // initialization of the new node
            NodePtr newNode = new patientCase();
            newNode->patientName = name;
            newNode->caseDesc = desc;
            newNode->priority = level;
            newNode->next = nullptr;

            if (front == nullptr) { // check if queue is empty
                front = newNode;
                rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }

        }

};


int main() {


    return 0;
}
