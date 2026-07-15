#include <iostream>
#include <limits>

class Queue { // uses doubly linked list
    private:

        struct patientCase { // task node blueprint
            std::string patientName, caseDesc; // caseDesc is the description of the patient's case
            std::string patientID; // contains a unique identifier for the patient case
            int priority; // legend: 1 = non emergency, 2 = emergency, 3 = highly urgent emergency
            int dateMade[3], dateDischarged[3]; // legend of indices: 0 = Day, 1 = Month, 2 = Year
            patientCase* next, *prev;
            bool discharged = false;
        };

        typedef patientCase* NodePtr;

        NodePtr front = nullptr;
        NodePtr rear = nullptr;
        int numItems = 0;
    
    public:

        bool is_leap_year(int year) { // for leap year calculation lang
        if (year % 400 == 0) {
            return true;
        }

        if (year % 100 == 0) {
            return false;
        }

        return year % 4 == 0;
    }

    int days_in_month(int month, int year) {

        if (month == 2) {
            if (is_leap_year(year)) {
                return 29;
            }

            return 28;
        }

        if (month == 4 ||
            month == 6 ||
            month == 9 ||
            month == 11) {

            return 30;
        }

        return 31;
    }


     void show_current_day() { // added this just in case
        std::cout << "Current simulated date: "
                  << currentDate[0] << "/"
                  << currentDate[1] << "/"
                  << currentDate[2] << '\n';
    }

    void move_one_day() {

        currentDate[0]++;

        int maximumDays = days_in_month(
            currentDate[1],
            currentDate[2]
        );

        if (currentDate[0] > maximumDays) {
            currentDate[0] = 1;
            currentDate[1]++;
        }

        if (currentDate[1] > 12) {
            currentDate[1] = 1;
            currentDate[2]++;
        }

        std::cout << "Moved to the next day.\n";
        show_current_day();
    }

    void view_patient_details(const std::string& patientName) {

        NodePtr traverse = front;

        while (traverse != nullptr) {

            if (traverse->patientName == patientName) {

                std::cout << "\n--- Patient Details ---\n";

                std::cout << "Patient Name: "
                          << traverse->patientName << '\n';

                std::cout << "Patient ID: "
                          << traverse->patientID << '\n';

                std::cout << "Case Description: "
                          << traverse->caseDesc << '\n';

                std::cout << "Priority: "
                          << traverse->priority << '\n';

                std::cout << "Date Admitted: "
                          << traverse->dateMade[0] << "/"
                          << traverse->dateMade[1] << "/"
                          << traverse->dateMade[2] << '\n';

                if (traverse->discharged) {

                    std::cout << "Status: Discharged\n";

                    std::cout << "Date Discharged: "
                              << traverse->dateDischarged[0] << "/"
                              << traverse->dateDischarged[1] << "/"
                              << traverse->dateDischarged[2] << '\n';

                } else {
                    std::cout << "Status: Not Discharged\n";
                }

                return;
            }

            traverse = traverse->next;
        }

        std::cout << "Patient not found.\n";
    }

    void mark_patient_as_discharged(
        const std::string& patientName,
    ) {

        NodePtr traverse = front;

        while (traverse != nullptr) {

            if (traverse->patientName == patientName) {

                if (traverse->discharged) {

                    std::cout
                        << "This patient has already been discharged.\n";

                    return;
                }

                traverse->discharged = true;

                traverse->dateDischarged[0] = currentDate[0];
                traverse->dateDischarged[1] = currentDate[1];
                traverse->dateDischarged[2] = currentDate[2];

                std::cout
                    << "Patient marked as discharged.\n";

                return;
            }

            traverse = traverse->next;
        }

        std::cout << "Patient not found.\n";
    
    };
        void sort_node_in_queue(NodePtr caseNode) { 
            if (caseNode->prev == nullptr) { // is a check in case the case node is at the front
                return;
            } 
            while (caseNode->prev->priority < caseNode->priority) { // is true when the node to the left has a priority less than the current case node
                NodePtr prevNode = caseNode->prev; // is the node to the left of the current case node
                NodePtr prevprevNode = prevNode->prev; // stores the node before the node to the left of the current case node
                NodePtr nextNode = caseNode->next; // stores the node currently after the case node (to the right of case node)
                if (prevprevNode == nullptr) { // is for the scenario when current case node is second to the front node
                    prevNode->next = caseNode->next; // sets the next node of the node to the left of case node to the right of case node
                    caseNode->next = prevNode; // turns the node formerly to the left to now the node to the right of case node
                    caseNode->prev = nullptr; // because case node is now the front, its left pointer is now null
                    prevNode->prev = caseNode; // completes the link of case node and the node formerly to the left which is now the right node
                    if (nextNode != nullptr) {nextNode->prev = prevNode;} // links the node formerly the left node to the node formerly the right node
                    front = caseNode; // sets the current case node as the new front 
                } else {
                    prevprevNode->next = caseNode; // links the node before the previous node to the case node
                    prevNode->next = caseNode->next; // links the previous node's next pointer to the node currently after case node
                    if (prevNode->next == nullptr) {rear = prevNode;} // happens if the swap occurs between the second to the last and the last nodes
                    caseNode->next = prevNode; // switches the node after case node into the former previous node
                    prevNode->prev = caseNode; // completes the switch
                    if (nextNode != nullptr) {nextNode->prev = prevNode;} // links the node formerly after case node to the new next node ONLY if next node exists
                    caseNode->prev = prevprevNode; // links the case node the the previous node of the formerly previous node
                }
            } 
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
            newNode->prev = nullptr;

            if (front == nullptr) { // check if queue is empty
                front = newNode;
                rear = newNode;
            } else {
                newNode->prev = rear;
                rear->next = newNode;
                rear = newNode;
                numItems++; // increments the total items count
                sort_node_in_queue(newNode);
            }

        }
};

int main() {

    int currentDate[3] = {16, 7, 2026}; // starting simulation date: 16/07/2026 (tentative)

    return 0;
}
