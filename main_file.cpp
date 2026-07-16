#include <iostream>
#include <cctype>
#include <limits>
#include <string>

class list {
    private:

        struct patientCase { // task node blueprint
            std::string patientName, caseDesc; // caseDesc is the description of the patient's case
            std::string patientID; // contains a unique identifier for the patient case
            int priority; // legend: 1 = non emergency, 2 = emergency, 3 = highly urgent emergency
            int dateMade[3], dateDischarged[3]; // legend of indices: 0 = Day, 1 = Month, 2 = Year
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
        
        void search() { //searches all similar nodes
            char choice;
            
            do {
                std::string input;
                NodePtr current = front;
                searchResults *crest = nullptr, *conductor; //conductor will traverse like how a conductor moves between train carts, crest is the head/front of the list
                int GotYa = 1; //just a counter if it got something
                
                while(true) { //input loop
                    std::cout << "Input patient name or ID: ";
                    std::getline(std::cin, input);
                    
                    if(input.length() == 0) {
                        std::cout << "You didn't input anything\n";
                        continue;
                    }
                    else {
                        std::string lower_input = lowercase(input);
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
                            if(GotYa == 1) {
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
                    
                    int selection;
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
};


int main() {


    return 0;
}
