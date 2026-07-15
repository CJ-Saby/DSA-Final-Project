#include <iostream>
#include <cctype>

class list {
    private:

        struct patientCase { // task node blueprint
            std::string patientName, caseDesc; // caseDesc is the description of the patient's case
            std::string patientID; // contains a unique identifier for the patient case
            int priority; // legend: 1 = non emergency, 2 = emergency, 3 = highly urgent emergency
            int dateMade[3], dateCompleted[3]; // legend of indices: 0 = Day, 1 = Month, 2 = Year
            patientCase* next;
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
        
        void search() {
            std::string input;
            NodePtr current = head;
            bool found = false;
            while(true) {
                std::getline(std::cin, input);
                std::cout << "Input patient name or ID: ";
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
                        while(current != nullptr) {
                            std::string lower_name = lowercase(current->patientName);
                            std::string lower_ID = lowercase(current->patientID);
                        }
                    }
                }
            }
        }
};


int main() {


    return 0;
}
