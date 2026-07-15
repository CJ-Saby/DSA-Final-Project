#include <iostream>
#include <string>

class list {
private:

    struct patientCase {
        std::string patientName, caseDesc; // caseDesc is the description of the patient's case
            std::string patientID; // contains a unique identifier for the patient case
            int priority; // legend: 1 = non emergency, 2 = emergency, 3 = highly urgent emergency
            int dateMade[3], dateDischarged[3]; // legend of indices: 0 = Day, 1 = Month, 2 = Year

        bool discharged = false; // added for discharge status

        patientCase* next = nullptr;
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
    }
};

int main() {

     int currentDate[3] = {16, 7, 2026}; // starting simulation date: 16/07/2026 (tentative)

    return 0;
}
