#include <iostream>
#include <cctype>
#include <limits>
#include <string>
#include <random>
#include <cstdlib>

class Queue { // uses doubly linked list
    private:

        struct patientCase { // task node blueprint
            std::string patientName, caseDesc; // caseDesc is the description of the patient's case
            std::string patientID; // contains a unique identifier for the patient case
            int priority; // legend: 1 = non emergency, 2 = emergency, 3 = highly urgent emergency
            int dateMade[3] = {0}, dateDischarged[3] = {0}; // initialize dates to 0 by default (legend of indices: 0 = Day, 1 = Month, 2 = Year)
            patientCase* next, *prev;
            bool discharged = false;
        };
        
        struct searchResults {
            patientCase *foundNode;
            searchResults *next, *prev;
            int num;
        };
        
        std::string lowercase(std::string initial) { // turns a string into lowercase
            std::string lower = initial;
            for(int a = 0;a < lower.length();a++) {
                lower[a] = tolower(lower[a]);
            }
            return lower;
        }
        
        typedef patientCase* NodePtr;
        NodePtr front = nullptr;
        NodePtr rear = nullptr;
        int numItems = 0;

        //Discharged Patients
        NodePtr dischargedFront = nullptr;
        NodePtr dischargedRear = nullptr;
    
    public:
        
        void update_node(searchResults *point) {
            NodePtr current;
            current = point->foundNode;
        }
        
        void remove_node(searchResults *point) {
            NodePtr current = point->foundNode;
            if(current->prev == nullptr && current->next == nullptr) {
                delete current;
                front = nullptr;
                numItems--;
            }
            else if(current->prev != nullptr && current->next == nullptr) {
                front = front->next;
                delete current;
                numItems--;
            }
            else if(current->prev == nullptr && current->next != nullptr) {
                current = current->next;
                delete current->prev;
                current->prev = nullptr;
                front = current;
                numItems--;
            }
            else {
                current->next->prev = current->prev;
                current->prev->next = current->next;
                delete current;
                numItems--;
            }
        }

        ~Queue() {
            NodePtr current = front;
            while (current != nullptr) {
                NodePtr nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        std::string id_random() {
            const std::string possibleChar = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            std::string id = "";
            for (int i = 0; i < 6; i++) {
                id += possibleChar[rand() % 62];
            }
            return id;
        }

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
        
        void search() { //searches all similar nodes
            char choice;
            
            do {
                std::string input;
                NodePtr current = front;
                searchResults *crest = nullptr, *conductor; //conductor will traverse like how a conductor moves between train carts, crest is the head/front of the list
                int GotYa = 1; //just a counter if it got something
                std::string lower_input;
                int selection;
                
                while(true) { //input loop
                    std::cout << "Input patient name or ID: ";
                    std::getline(std::cin, input);
                    
                    if(input.length() == 0) {
                        std::cout << "You didn't input anything\n";
                        continue;
                    }
                    else {
                        lower_input = lowercase(input);
                        break;
                    }
                }
                
                if(current == nullptr) {
                    std::cout << "The Queue is Empty\n";
                }
                else {
                    while(current != nullptr) { //searching and recording each found node
                        std::string lower_name = lowercase(current->patientName);
                        std::string lower_ID = lowercase(current->patientID);
                                
                        if(lower_name.find(lower_input) != std::string::npos || lower_ID.find(lower_input) != std::string::npos) {
                            if (GotYa == 1) {
                                crest = new searchResults;
                                conductor = crest;
                                conductor->foundNode = current;
                                conductor->prev = nullptr;
                                conductor->next = nullptr;
                                conductor->num = GotYa;
                                GotYa++;
                            }
                            else {
                                conductor->next = new searchResults;
                                conductor->next->prev = conductor;
                                conductor = conductor->next;
                                conductor->foundNode = current;
                                conductor->next = nullptr;
                                conductor->num = GotYa;
                                GotYa++;
                            }
                        }
                        current = current->next;
                    }
                            
                    if(crest == nullptr) {
                        std::cout << "No matches found\n";
                    }
                    else {
                        conductor = crest;
                        while(conductor != nullptr) { //displaying the found nodes
                            std::cout << "[" << conductor->num << "]\n";
                            std::cout << "Name: " << conductor->foundNode->patientName << std::endl;
                            std::cout << "ID: " << conductor->foundNode->patientID << std::endl;
                            conductor = conductor->next;
                        }
                    
                        while(true) {
                            std::cout << "\nEnter a Number: ";
                            std::cin >> selection;
                            if(std::cin.fail() || selection >= GotYa) {
                                std::cout << "Invalid Input!\n";
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                continue;
                            }
                            else {
                                conductor = crest;
                                break;
                            }
                        }
                    }
                    
                    int choice;
                    while(conductor != nullptr) {
                        if(conductor->num == selection) {
                            while(true) {
                                std::cout << "\n[1] Edit\n[2] Delete\n[3] Exit\nInput: ";
                                std::cin >> choice;
                                if(std::cin.fail()) {
                                    std::cout << "Invalid Input!\n";
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    continue;
                                }
                                else if(choice < 1 || choice > 3) {
                                    std::cout << "Invalid Input!\n";
                                    continue;
                                }
                                else break;
                            }
                            
                            if(choice == 1) {
                                update_node(conductor);
                            }
                            else if(choice == 2) {
                                remove_node(conductor);
                                std::cout << "Node Deleted\n";
                            }
                            else if(choice == 3) {
                                std::cout << "Returning\n";
                            }
                            break;
                        }
                        else {
                            conductor = conductor->next;
                        }
                    }
                    
                    searchResults *cleaner;
                    while(crest != nullptr) {
                        cleaner = crest;
                        crest = crest->next;
                        delete cleaner;
                    }
                    
                    
                    std::cout << "\nContinue(Enter y if yes, anything else if no): ";
                    std::cin >> choice;
                        
                }
            } while(tolower(choice) == 'y');
        }
        
        void show_current_day(int currDate[]) { // added this just in case
            std::cout << "Current simulated date: "
                    << currDate[0] << "/"
                    << currDate[1] << "/"
                    << currDate[2] << '\n';
        }

        void move_one_day(int currDate[]) {

            currDate[0]++;

            int maximumDays = days_in_month(
                currDate[1],
                currDate[2]
            );

            if (currDate[0] > maximumDays) {
                currDate[0] = 1;
                currDate[1]++;
            }

            if (currDate[1] > 12) {
                currDate[1] = 1;
                currDate[2]++;
            }

            std::cout << "Moved to the next day.\n";
            show_current_day(currDate);
        }

        void view_patient_details(const std::string& id) {

            NodePtr traverse = front;

            while (traverse != nullptr) {

                if (traverse->patientID == id) {

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

        void mark_patient_as_discharged(const std::string& id, int currDate[]) {

            NodePtr traverse = front;

            while (traverse != nullptr) {

                if (traverse->patientID == id) {

                    if (traverse->discharged) {

                        std::cout
                            << "This patient has already been discharged.\n";

                        return;
                    }

                    traverse->discharged = true;

                    traverse->dateDischarged[0] = currDate[0];
                    traverse->dateDischarged[1] = currDate[1];
                    traverse->dateDischarged[2] = currDate[2];

                    std::cout
                        << "Patient marked as discharged.\n";

                    return;
                }

                traverse = traverse->next;
            }

            std::cout << "Patient not found.\n";
        
        }

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

        void add_record(int date[]) { 
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
            newNode->dateMade[0] = date[0];
            newNode->dateMade[1] = date[1];
            newNode->dateMade[2] = date[2];
            newNode->patientID = id_random();
            newNode->next = nullptr;
            newNode->prev = nullptr;

            if (front == nullptr) { // check if queue is empty
                front = newNode;
                rear = newNode;
            } else {
                newNode->prev = rear;
                rear->next = newNode;
                rear = newNode;
                sort_node_in_queue(newNode);
            }
            numItems++; // increments the total items count
        }

        void view_all() {
            if (front == nullptr) {
                std::cout << "\n--- No patient records found. The queue is empty. ---\n";
                return;
            }

            NodePtr temp = front;
            int count = 1;
            
            std::cout << "\n\t\tCURRENT PATIENT QUEUE           \n\n"; 

            while (temp != nullptr) {
                std::cout <<"Position in Queue: " << count << "\n";
                std::cout <<"Patient Name:      " << temp->patientName << "\n";
            
                // Shows the urgency of the patient is
                std::cout <<"Priority Level:    "<<temp->priority<<"(";
                if (temp->priority == 1) {
                    std::cout << "Non-emergency";
                } else if (temp->priority == 2) {
                    std::cout << "Emergency";
                } else if (temp->priority == 3) {
                    std::cout << "Highly Urgent Emergency";
                } 
                std::cout << ")\n";

                std::cout <<"Date Registered:   " 
                          << temp->dateMade[0] << "/"   // Day
                          << temp->dateMade[1] << "/"   // Month
                          << temp->dateMade[2] << "\n"; // Year
                
                std::cout << "---------------------------------------------\n";
                
                temp = temp->next; // Move to the next patient in line
                count++;
            }
            int choice;
            std::cout << "1.View patient\n"; 
            std::cout << "2.Back\n";
            while (true) {
            std::cout << "Enter choice: ";
        
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Try again.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (choice == 1){
                int targetPos; // selecting the desired patient through its number in the list
                std::cout << "Select patient no: " ;
                        if (std::cin >> targetPos) {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        patient_position(targetPos);
                    }
                    break;

            } else if (choice == 2){   
                break;
            } 
                else {
                std::cout << "Please select a valid option.\n";
            }
        }
        }
        void view_discharged_patients() {
            if (dischargedFront == nullptr) {
                std::cout << "\n--- No discharged patient history found. ---\n";
                return;
            }

            NodePtr temp = dischargedFront;
            int count = 1;

             std::cout << "\n\t\tDISCHARGED PATIENTS           \n\n";

            while (temp != nullptr) {
                std::cout << "Discharged Record #" << count << "\n";
                std::cout << "Patient Name:      " << temp->patientName << "\n";
                std::cout << "Case Description:  " << temp->caseDesc << "\n";
                std::cout << "Date Registered:   " 
                          << temp->dateMade[0] << "/" << temp->dateMade[1] << "/" << temp->dateMade[2] << "\n";
                std::cout << "Date Discharged:   " 
                          << temp->dateDischarged[0] << "/" << temp->dateDischarged[1] << "/" << temp->dateDischarged[2] << "\n";
                std::cout << "---------------------------------------------\n";

                temp = temp->next;
                count++;
            }
        }

        void patient_position(int position) {
            NodePtr temp = front;
            int count = 1;

            while (temp != nullptr && count < position) {
                temp = temp->next;
                count++;
            }

            if (temp == nullptr || position < 1) {
                std::cout << "\nError: Invalid position choice.\n";
                return;
            }

            // Print deep details
            view_patient_details(temp->patientName);
        }
};

int main() {

    int currentDate[3] = {16, 7, 2026}; // starting simulation date: 16/07/2026 (tentative)

    return 0;
}