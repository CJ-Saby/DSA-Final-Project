#include <iostream>
#include <limits>
#include <string>

class Queue {
    private:

        struct patientCase { // task node blueprint
            std::string patientName, caseDesc; // caseDesc is the description of the patient's case
            std::string patientID; // contains a unique identifier for the patient case
            int priority; // legend: 1 = non emergency, 2 = emergency, 3 = highly urgent emergency
            int dateMade[3], dateDischarged[3]; // legend of indices: 0 = Day, 1 = Month, 2 = Year
            bool discharged = false; // added for discharge status
            patientCase* next;
        };

        typedef patientCase* NodePtr;

        NodePtr front = nullptr;
        NodePtr rear = nullptr;
        int numItems = 0;

        //Discharged Patients
        NodePtr dischargedFront = nullptr;
        NodePtr dischargedRear = nullptr;
    
    public:
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



        
        /*void simulate_test_cases() {// ~ ~ ~ DO NOT ADD TS, THIS IS ONLY FOR SIMULATION PURPOSES [I GOT LAZY IN ADDING PATIENTS NGL] ~ ~ ~
            // A single unified structure for all mock patients
            struct MockPatient {
                std::string name;
                std::string desc;
                int admDay, admMonth, admYear;
                int disDay, disMonth, disYear; // Left as 0 if they aren't discharged yet
                int priority;
                bool isDischarged;
            };

            // All 7 simulated patients combined into one list
            MockPatient dataset[] = {

                {"Alice Smith",   "Routine checkup and physical exam",         15, 7, 2026, 0, 0, 0, 1, false},
                {"Bob Jones",     "Severe chest pain and shortness of breath", 16, 7, 2026, 0, 0, 0, 3, false},
                {"Charlie Brown", "Deep laceration on the left forearm",       14, 7, 2026, 0, 0, 0, 2, false},
                {"Diana Prince",  "Suspected fractured ankle from a fall",     16, 7, 2026, 0, 0, 0, 2, false},
                {"Evan Wright",   "High fever and unresponsive to medication", 17, 7, 2026, 0, 0, 0, 3, false},
                {"Frank Castle",  "Minor concussion treatment",               10, 7, 2026, 11, 7, 2026, 1, true},
                {"Grace Hopper",  "Acute seasonal allergy recovery",          12, 7, 2026, 12, 7, 2026, 1, true}
            };

           

            for (const auto& patient : dataset) {
                // Create a generic node
                NodePtr newNode = new patientCase();
                newNode->patientName = patient.name;
                newNode->caseDesc = patient.desc;
                newNode->dateMade[0] = patient.admDay;
                newNode->dateMade[1] = patient.admMonth;
                newNode->dateMade[2] = patient.admYear;
                newNode->priority = patient.priority;
                newNode->discharged = patient.isDischarged;
                newNode->next = nullptr;

                if (patient.isDischarged) {
                    // 1. Store discharge dates
                    newNode->dateDischarged[0] = patient.disDay;
                    newNode->dateDischarged[1] = patient.disMonth;
                    newNode->dateDischarged[2] = patient.disYear;

                    // 2. Append directly to discharged history list
                    if (dischargedFront == nullptr) {
                        dischargedFront = newNode;
                        dischargedRear = newNode;
                    } else {
                        dischargedRear->next = newNode;
                        dischargedRear = newNode;
                    }
                } else {
                    // 3. Process priority queue sorting rules for active patients
                    if (front == nullptr) { 
                        front = newNode;
                        rear = newNode;
                    } else if (newNode->priority > front->priority) { 
                        newNode->next = front;
                        front = newNode;
                    } else { 
                        NodePtr current = front;
                        while (current->next != nullptr && current->next->priority >= newNode->priority) {
                            current = current->next;
                        }
                        newNode->next = current->next;
                        current->next = newNode;
                        if (newNode->next == nullptr) {
                            rear = newNode;
                        }
                    }
                }
            }
        }*/

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
    Queue Clinic;
    //Clinic.simulate_test_cases(); //Remove this in final

    int choice;

    while (true) {
        std::cout << "~~~~~~~~~~~~~~~~~~~~\nTHIS IS THE START BRUH\n~~~~~~~~~~~~~~~~~~~~\n";
        std::cout << "1. Add Patient Record\n";
        std::cout << "2. View All Patients\n";
        std::cout << "3. View Discharged Patients\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            Clinic.add_record();
        } else if (choice == 2) {
            Clinic.view_all();
        } else if (choice == 3) {
            Clinic.view_discharged_patients();
        } else if (choice == 4) {
            
            break;
        } else {
            std::cout << "Please select a valid option.\n";
        }
    }

    return 0;
}
