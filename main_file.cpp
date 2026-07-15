#include <iostream>
#include <cctype>

class list {
    private:

        struct patientCase { // task node blueprint
            std::string patientName, caseDesc; // caseDesc is the description of the patient's case
            std::string patientID; // contains a unique identifier for the patient case
            int priority; // legend: 1 = non emergency, 2 = emergency, 3 = highly urgent emergency
            int dateMade[3], dateCompleted[3]; // legend of indices: 0 = Day, 1 = Month, 2 = Year
            patientCase* next, *prev;
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
        patientCase *head = nullptr;

    public:

        void view_task_details (std::string patientName){

            // WIP

        }
        
        void update_task() {
            NodePtr current;
        }
        
        void search() { //searches all similar nodes
            std::string input;
            NodePtr current = head;
            searchResults *crest = nullptr, *conductor;
            bool found = false;
            int GotYa = 1;
            
            while(true) { //input loop
                std::cout << "Input patient name or ID: ";
                std::getline(std::cin, input);
                if(input.length() == 0) {
                    std::cout << "You didn't input anything\n";
                    continue;
                }
                else {
                    std::string lower_input = lowercase(input);
                    if(current == nullptr) {
                        std::cout << "The Queue is Empty\n";
                        break;
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
                                    conductor->next = nullptr;
                                    conductor->num = GotYa;
                                    GotYa++;
                                }
                            }
                            current = current->next;
                        }
                        while(conductor != nullptr) { //displaying the found nodes
                            conductor = crest;
                            std::cout << "[" << conductor->num << "]\n";
                            std::cout << "Name: " << conductor->foundNode->patientName << std::endl;
                            std::cout << "ID: " << conductor->foundNode->patientID << std::endl;
                        }
                    }
                }
            }
        }
};


int main() {


    return 0;
}
