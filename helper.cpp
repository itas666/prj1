#include "helper.h"

//A made up clear screen function since we cannot use system libraries
void clear_screen(){
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void print_menu(){
    clear_screen();
    std::cout << "--------MENU--------" << std::endl;
    std::cout << "1. Add new event" << std::endl;
    std::cout << "2. Add booking" << std::endl;
    std::cout << "3. Cancel a booking" << std::endl;
    std::cout << "4. List all events" << std::endl;
    std::cout << "5. List details of an event" << std::endl;
    std::cout << "6. Load data from event file" << std::endl;
    std::cout << "7. Save all data into event file" << std::endl;
    std::cout << "8. Provide empty event file for editing" << std::endl;
    std::cout << std::endl;
    std::cout << "0. Exit" << std::endl;
}
//A check to see if a year is a leap year for the day check
bool is_leap_year(int auxYear){
    if (auxYear % 4 == 0){
        if (auxYear % 100 == 0){
            if (auxYear % 400 == 0){
                return true;
            }else{
                return false;
            }
        }else{
            return true;
        }
    }else{
        return false;
    }
}
//A simple check that takes a value and checks if it is in between
// the parameters 2 and 3
bool is_value_between(int value, int lowBound, int highBound){
    if((value >= lowBound) && (value <= highBound)) return true;

    return false;
}
//Takes day, month and year to see if the date exists
//IE month is between 1 and 12, day exists and is between 1 and 28-31
bool date_exists(int auxDay, int auxMonth, int auxYear){
    bool isLeap = is_leap_year(auxYear);
    int maxDay = 0;

    if(!is_value_between(auxMonth, 1, 12)){
        std::cout << "Incorrect month value '" << auxMonth
        << "', aborting operation." << std::endl;
        return false;
    }

    switch(auxMonth){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            maxDay = 31;
            break;
        case 2:
            if(isLeap) maxDay = 29;
            else maxDay = 28;
            break;
        default:
            maxDay = 30;
    }

    if(!is_value_between(auxDay, 1, maxDay)){
        std::cout << "Incorrect day value '" << auxDay
        << "', aborting operation." << std::endl;
        return false;
    }

    return true;
}

bool time_exists(int auxHour, int auxMinute){
    if(!is_value_between(auxHour, 0, 23)){
        std::cout << "Incorrect hour value '" << auxHour
        << "', aborting operation." << std::endl;
        return false;
    }
    if(!is_value_between(auxHour, 0, 59)){
        std::cout << "Incorrect minutes value '" << auxMinute
        << "', aborting operation." << std::endl;
        return false;
    }
    return true;
}
//Function to check if date format is actually in format we want
//and not any rubish number
bool is_date_format_correct(std::string dateString){
    std::regex pattern("\\b\\d{2}/\\d{2}/\\d{4}\\ \\d{2}[:]\\d{2}\\b");
    std::smatch result;

    regex_search(dateString, result, pattern);
    
    if (result.str(0) == "") {
        std::cout << "Incorrect date format '" << dateString
                << "', aborting operation." << std::endl;
        return false;
    }

    int auxDay, auxMonth, auxYear, auxHour, auxMinute = 0;

    auxDay = std::stoi(dateString.substr(0, 2));
    auxMonth = std::stoi(dateString.substr(3, 2));
    auxYear = std::stoi(dateString.substr(6, 4));
    auxHour = std::stoi(dateString.substr(11, 2));
    auxMinute = std::stoi(dateString.substr(14, 2));

    // If the date OR the time DON'T exist, return false and throw error
    if(
        (!date_exists(auxDay, auxMonth, auxYear)) ||
        (!time_exists(auxHour, auxMinute))
    ){
        std::cout << "Incorrect date string given '" << dateString
                << "'. Uncontrolled date exception..." << std::endl;
        return false;
    }

    return true;
}

std::string read_date(){
    std::string dd, MM, YYYY, hh, mm;
    std::string dateString;
    int errorFlag = 0;

    std::cout << "Input date in DD/MM/YYYY HH:MM format: ";
    std::getline(std::cin, dateString);
    
    if(is_date_format_correct(dateString)){
        return dateString;
    }
    return "";
}

Node* add_event(Node* root){
    std::string name, date, type;
    std::shared_ptr<Event> newEvent;

    std::cout << "Enter the name of the event: " << std::endl;
    std::getline(std::cin, name);
    if((date = read_date()) == ""){
        return root;
    };
    std::cout << "What type of event is it : " << std::endl;
    std::cout << "1. Film" << std::endl;
    std::cout << "2. Standup comedy" << std::endl;
    std::cout << "3. Live music" << std::endl;
    std::cout << "Enter option: ";
    std::getline(std::cin, type);
    if(type == "1"){
        std::cout << "Is the Film is 3D? Y = yes/N = No: ";
        std::getline(std::cin, type);
        if(type == "Y"){
            newEvent = std::make_shared<Film>(name, date, true, 0);
        }else if(type == "N"){
            newEvent = std::make_shared<Film>(name, date, false, 0);
        }else{
            std::cout << "Incorrect option, aborting process" << std::endl;
            return root;
        }
        std::cout << "Saving data to memory..." << std::endl;
        root = insert(root, newEvent);
        std::cout << "Done!" << std::endl;
    }else if(type == "2"){

    }else if(type == "3"){

    }else{
        std::cout << "Invalid option, aborting process. " << std::endl;
        return root;
    }

    return root;
}

Node* add_booking(Node* root){
    Node* auxNode;
    std::string eventName;
    std::cout << "Enter the name of the event to search for: ";
    getline(std::cin, eventName);

    auxNode = search(root, eventName);

    if (auxNode == NULL){
        std::cout << "Event not found" << std::endl;
        return root;
    }

    auxNode->key->readEventData();
    auxNode->key->makeBooking();

    return root;
}

Node* cancel_booking(Node* root){
    Node* auxNode;
    std::string eventName;
    std::cout << "Enter the name of the event to search for: ";
    getline(std::cin, eventName);

    auxNode = search(root, eventName);

    if (auxNode == NULL){
        std::cout << "Event not found" << std::endl;
        return root;
    }
    auxNode->key->readEventData();
    auxNode->key->removeBooking();
    
    return root;
}

void list_events(Node* root){
    inOrder(root);
    return;
}

void list_specific_event(Node* root){
    Node* auxNode;
    std::string eventName;
    std::cout << "Enter the name of the event to search for: ";
    getline(std::cin, eventName);

    auxNode = search(root, eventName);

    if (auxNode == NULL){
        std::cout << "Event not found" << std::endl;
        return;
    }
    auxNode->key->readEventData();
}

Node* load_from_file(Node* root){
    Node* selectedEvent = NULL;
    std::string aux;
    std::cout << "Enter the name of the file to load events from.\n"
            << " This file needs to be in the program's folder: ";
    std::getline(std::cin, aux);
    bool errorFlag;

    std::string filePath = ".\\" + aux;
    std::ifstream myFile;
    std::string splitWord, line, auxSeatsList;

    std::string eventName, eventDate, eventType, eventSeatsTaken, seatsString;
    
    std::string delimiter = ", ";
    std::string seatsDelimiter = "-";
    int pos = 0;
    myFile.open(filePath);

    
    if(!myFile.is_open()) {
       std::cout << "Error opening file " << filePath << ". Maybe the file doesn't exist\n";
       return root;
    }
    int lineCount = 1; //counts header
    getline(myFile, line); //Get header out of way
    while(getline(myFile, line)) {
        pos = 0;

        for(int i = 0; pos != std::string::npos; i++){
            pos = line.find(delimiter);
            splitWord = line.substr(0, pos);
            switch(i){
                case 0:
                    eventName = splitWord;
                    break;
                case 1:
                    eventDate = splitWord;
                    break;
                case 2:
                    eventType = splitWord;
                    break;
                case 3:
                    eventSeatsTaken = splitWord;
                    break;
                case 4:
                    seatsString = splitWord;
                    break;
            }
            line.erase(0, pos + (delimiter.length()));
        }

        if(is_date_format_correct(eventDate)){
            if((std::stoi(eventSeatsTaken) > 300)&&(eventType == "LM")){
                std::cout << "Event with too many bookings. Event not saved.";
            }else if(
                (std::stoi(eventSeatsTaken) > 200)&&
                ((eventType == "F2D")||(eventType == "F3D")||(eventType == "SC"))
            ){
                std::cout << "Event with too many bookings. Event not saved.";
            }else if(eventType == "F2D"){
                root = insert(root, std::make_shared<Film>(eventName, eventDate, false, std::stoi(eventSeatsTaken)));
            }else if(eventType == "F3D"){
                root = insert(root, std::make_shared<Film>(eventName, eventDate, true, std::stoi(eventSeatsTaken)));
            }else if(eventType == "LM"){
                root = insert(root, std::make_shared<LiveMusic>(eventName, eventDate, std::stoi(eventSeatsTaken)));
            }else if(eventType == "SC"){
                root = insert(root, std::make_shared<StandupComedy>(eventName, eventDate));
                selectedEvent = search(root, eventName);

                if(selectedEvent != NULL){
                    pos = 0;
                    for(int i = 0; pos != std::string::npos; i++){
                        pos = seatsString.find(seatsDelimiter);
                        splitWord = seatsString.substr(0, pos);

                        if(!is_string_number(splitWord)){
                            std::cout << "This seat is not a number, skipping..." << std::endl;
                        }else{
                            selectedEvent->key->makeBooking((std::stoi(splitWord)));
                        }
                        seatsString.erase(0, pos + (seatsDelimiter.length()));
                    }
                }
            }else{
                std::cout << "Incorrect event type '" << eventType << "'"
                << ", or other unhandled error, skipping insertion. ";
            }
        }
        std::cout << "Column " << lineCount << " processed..." << std::endl;
        lineCount++;
    }
    myFile.close();

    return root;
}

void save_to_file(Node* root){
    std::string fileName, auxString;
    std::cout << "Enter the name of the file to save the data in: ";
    
    std::getline(std::cin, fileName);

    std::ofstream outFile(fileName, std::ios::out | std::ios::app);

    auxString = "EVENT NAME, DD/MM/YYYY HH:MM, TYPE (F2D or F3D, LM, SC), SEATS TAKEN (1-2-...-200 or 300)\n";
    auxString = auxString + send_tree_to_file(root);

    outFile << auxString;
    outFile.flush();
    outFile.close();

    return;
}

void create_template(){
    std::string filePath = "./events_template.csv";
    std::ofstream outFile(filePath, std::ios::out | std::ios::app);
    std::string outString;

   
    outString = outString + "EVENT NAME, DD/MM/YYYY HH:MM, TYPE (F, LM, SC), SEATS TAKEN (1-2-...-200 or 300)\r\n";

    outFile << outString;
    outFile.flush();
    outFile.close();

    return;
}

void press_key(){
    std::string aux;
    std::cout << "Press the enter key to continue...";
    std::getline(std::cin, aux);
}

bool is_string_number(std::string myString){
    for (char const &c : myString) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}