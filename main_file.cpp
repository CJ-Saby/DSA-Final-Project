#include <iostream>
#include <cctype>
#include <limits>
#include <string>
#include <random>
#include <cstdlib>
#include <fstream>
#include <sstream>

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
        
        typedef patientCase* NodePtr;
        NodePtr front = nullptr;
        NodePtr rear = nullptr;
        int numItems = 0;

    public:

		bool found = false;
    
        std::string lowercase(std::string initial) { // turns a string into lowercase
            std::string lower = initial;
            for(int a = 0;a < lower.length();a++) {
                lower[a] = tolower(lower[a]);
            }
            return lower;
        }

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
                current->prev->next = nullptr;
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

        void clear_queue() {
            NodePtr current = front;
            while (current != nullptr) {
                NodePtr nextNode = current->next;
                delete current;
                current = nextNode;
            }
            front = nullptr;
            rear = nullptr;
            numItems = 0;
            std::cout << "Queue successfully cleared." << std::endl;
        }

        ~Queue() {
            clear_queue();
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
			found = false;
            
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
					found = false;
                }
                else {
					found = true;
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
						found = false;
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
                            if(std::cin.fail() || selection < 1 || selection >= GotYa) {
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
                    
                    //open the file in append mode (creates it if it doesn't exist)
                    std::ofstream outFile("discharged_history.txt", std::ios::app);
                    if (!outFile){                        
                    std::cout << "Error: Could not open file to save record.\n";
                        return;
                    }

                    //writes the patient's deets into the file
                    outFile << "Patient Name: " << traverse->patientName << "\n"
                            << "ID: " << traverse->patientID << "\n"
                            << "Case: " << traverse->caseDesc << "\n"
                            << "Date Admitted: " << traverse->dateMade[0] << "/" 
                                                << traverse->dateMade[1] << "/" 
                                                << traverse->dateMade[2] << "\n"
                            << "Date Discharged: " << currDate[0] << "/" 
                                                << currDate[1] << "/" 
                                                << currDate[2] << "\n"
                            << "---------------------------------------------\n";
                    
                    outFile.close();
                    std::cout << traverse->patientName << " has been discharged and saved to file.\n";

                    // Removes the Patient in the Queue
                    if (traverse->prev == nullptr && traverse->next == nullptr) {
                        front = nullptr;
                        rear = nullptr;
                    } else if (traverse->prev == nullptr) { // Delete front
                        front = traverse->next;
                        front->prev = nullptr;
                    } else if (traverse->next == nullptr) { // Delete rear
                        rear = traverse->prev;
                        rear->next = nullptr;
                    } else { // Delete in middle
                        traverse->prev->next = traverse->next;
                        traverse->next->prev = traverse->prev;
                    }
                    
                    delete traverse;
                    numItems--;

                    return;
                }
                traverse = traverse->next;
            }

            std::cout << "Patient not found.\n";
        }

        void sort_node_in_queue(NodePtr caseNode) { 
            if (caseNode == nullptr || caseNode->prev == nullptr) { // is a check in case the case node is at the front or if queue is empty
                return;
            } 
            while (caseNode->prev != nullptr && caseNode->prev->priority < caseNode->priority) { // is true when the node to the left has a priority less than the current case node
                NodePtr prevNode = caseNode->prev; // is the node to the left of the current case node
                NodePtr prevprevNode = prevNode->prev; // stores the node before the node to the left of the current case node
                NodePtr nextNode = caseNode->next; // stores the node currently after the case node (to the right of case node)
                if (prevprevNode == nullptr) { // is for the scenario when current case node is second to the front node
                    prevNode->next = caseNode->next; // sets the next node of the node to the left of case node to the right of case node
                    caseNode->next = prevNode; // turns the node formerly to the left to now the node to the right of case node
                    caseNode->prev = nullptr; // because case node is now the front, its left pointer is now null
                    prevNode->prev = caseNode; // completes the link of case node and the node formerly to the left which is now the right node
                    if (nextNode != nullptr) { // links the node formerly the left node to the node formerly the right node
                        nextNode->prev = prevNode;
                    } else {
                        rear = prevNode;
                    }
                    front = caseNode; // sets the current case node as the new front 
                } else {
                    prevprevNode->next = caseNode; // links the node before the previous node to the case node
                    prevNode->next = nextNode; // links the previous node's next pointer to the node currently after case node
                    caseNode->next = prevNode; // switches the node after case node into the former previous node
                    prevNode->prev = caseNode; // completes the switch
                    if (nextNode != nullptr) { // links the node formerly after case node to the new next node ONLY if next node exists
                        nextNode->prev = prevNode;
                    } else {
                        rear = prevNode;
                    }
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
            std::ifstream inFile("discharged_history.txt");
            
            // If no files yet, then nobody has been discharged
            if (!inFile) {
                std::cout << "\n--- No discharged patient history found yet. ---\n";
                return;
            }

            std::cout << "\n\t\tDISCHARGED PATIENTS HISTORY\n\n";
            
            std::string line;
            // Read the file line by line and print it out
            while (std::getline(inFile, line)) {
                std::cout << line << '\n';
            }
            
            inFile.close();
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

            view_patient_details(temp->patientID);
        }

        void save_to_records() { // saves the current main queue to the records text file
            std::ofstream records("hospital_record.txt"); // file stream for accessing hospital record file
            if (records.is_open()) {
                NodePtr traverse = front;
                while (traverse != nullptr) { // the character following an * is an identifier for what type of information a certain line will hold. Used during text file reading
                    records << "n*" << traverse->patientName << '\n';
                    std::string safeDesc = traverse->caseDesc; // used to ensure there are no newlines in the middle of the description to be transferred over to the text file. 
                    for (char& c : safeDesc) {
                        if (c == '\n') {
                            c = ' ';
                        }
                    }
                    records << "d*" << safeDesc << '\n';
                    records << "i*" << traverse->patientID << '\n';
                    records << "p*" << traverse->priority << '\n';
                    records << "#*" << traverse->dateMade[0] << ' ' << traverse->dateMade[1] << ' ' << traverse->dateMade[2] << '\n';
                    records << "$*" << traverse->dateDischarged[0] << ' ' << traverse->dateDischarged[1] << ' ' << traverse->dateDischarged[2] << '\n';
                    records << "----------\n"; // separator for each record 

                    traverse = traverse->next; // for iterating through queue
                }
                std::cout << "Successfully saved queue to record text file." << std::endl;
            } else {
                std::cout << "Records failed to open." << std::endl;
            }
        }

        void load_to_queue() { // reads records text file and puts it into the priority queue
            std::ifstream records("hospital_record.txt"); // file stream for accessing hospital record file
            if (records.is_open()) { 
                std::string line;
                int priorityNum = 0, day = 0, month = 0, year = 0; // intialize variables with 0 for safety
                NodePtr currPatient = new patientCase();
                clear_queue(); // ensures that the current queue is empty before attempting to load record text file contents

                while (std::getline(records, line)) { // iterates through each line in the text file
                    if (line.length() < 2) {continue;} // safety in case a gap or insufficent character lne is present in the record

                    if (line[0] == 'n' && line[1] == '*') { // check if the line is a patient name line
                        currPatient->patientName = line.substr(2); // substr(2) ignores the previously added tags on each line
                    } 
                    else if (line[0] == 'd' && line[1] == '*') { // check if the line is a case description line
                        currPatient->caseDesc = line.substr(2);
                    } 
                    else if (line[0] == 'i' && line[1] == '*') { // check if the line is a patient id line
                        currPatient->patientID = line.substr(2);
                    } 
                    else if (line[0] == 'p' && line[1] == '*') { // check if the line is a priority line
                        try {
                            priorityNum = std::stoi(line.substr(2));
                            currPatient->priority = priorityNum;
                        } catch (const std::exception& e) {
                            currPatient->priority = 0;
                            std::cout << "Error: Priorty was corrupted in the record text file. Setting the current patient's priority to 0" << std::endl;
                        }
                    } 
                    else if (line[0] == '#' && line[1] == '*') { // check if the line is a date of when the case was made
                        std::stringstream (line.substr(2)) >> day >> month >> year; // used to parse through the tagged date string
                        currPatient->dateMade[0] = day;
                        currPatient->dateMade[1] = month;
                        currPatient->dateMade[2] = year;
                    } 
                    else if (line[0] == '$' && line[1] == '*') { // check if the line is a date of when the case was discharged
                        std::stringstream (line.substr(2)) >> day >> month >> year; // used to parse through the tagged date string
                        currPatient->dateDischarged[0] = day;
                        currPatient->dateDischarged[1] = month;
                        currPatient->dateDischarged[2] = year;
                    } 
                    else if (line == "----------") {
                        sort_node_in_queue(currPatient); // processes the node and puts it in the right order in the queue
                        currPatient = new patientCase(); // creates a new node to hold all the data and to be added to the queue
                        priorityNum = 0;
                        day = 0;
                        month = 0;
                        year = 0;
                    }
                }

                if (!currPatient->patientName.empty()) { // final check in the case that the reading loop ends and a patient record is still in the traversal node
                    sort_node_in_queue(currPatient);
                } else {
                    delete currPatient; // after reading, frees up the memory made from the temporary node used for traversal 
                }
                std::cout << "Successfully loaded record text file into queue." << std::endl;
            } else {
                std::cout << "Records failed to open." << std::endl;
            }
        }
};

int main() {
    Queue Records;
    int choice;
    int currentDate[3] = {16, 7, 2026};
	
	Records.load_to_queue();
    while(true) {
        std::cout << "===============================================\n";
        std::cout << "\t\tPatient Records\n";
        std::cout << "===============================================\n";
        std::cout << "[1] Add New Patient Record\n";
        std::cout << "[2] View Current Patient Queue\n";
        std::cout << "[3] Search Patient Database\n";
        std::cout << "[4] View Discharged Patients History\n";
		std::cout << "[5] Advance to Next Day\n";
        std::cout << "[6] Exit System\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if(std::cin.fail()) {
            std::cout << "Invalid Input!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if(choice > 5 || choice < 1) {
            std::cout << "Invalid Input!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            switch(choice) {
                case 1:
                    std::cout << "------------------ADD PATIENT------------------\n";
					Records.add_record(currentDate);
					Records.save_to_records();
                    break;
                case 2:
					std::cout << "------------------CURRENT QUEUE------------------\n";
                    Records.view_all();
                    break;
                case 3:
                    std::cout << "\n----------------SEARCH PATIENT----------------\n";
                    Records.search();
					if(Records.found) {
						Records.save_to_records();
					}
                    break;
                case 4:
					std::cout << "------------------DISCHARGED PATIENTS------------------\n";
                    Records.view_discharged_patients();
                    break;
                case 5:
                    std::cout << "\n----------------ADVANCING TIME----------------\n";
					Records.move_one_day(currentDate);
                	break;
				case 6:
					std::cout << "\nExiting clinic system. Goodbye!\n";
					Records.save_to_records();
                    return 0;
            }
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}
