#include "helper.h"

/*
REQUIREMENTS:
3 types of events:
    - Live music
        - Standing only (300 availability)
    - Standup comedy
        - Seated only (200 availability)
        - Seats numbered
    - Films
        - Seated only (200 availability)
I assume there is only one room with 200 seats
(not many rooms each with 200 seats)

Need an event class, and child classes for each type of event
Menu based program to manage the above
- Add bookings
- Cancel or refund bookings
- List all events
- List details and availability of event
- Load data from event (availability) file
- Save data to file (events and availability)
*/


 int main() {
    std::string option;
    Node* root = NULL;
    std::shared_ptr<Event> auxEvent = NULL;

    do{
        print_menu();
        std::getline(std::cin, option);

        //switch not suitable for string comparison
        if(option == "1"){
            root = add_event(root);
            press_key();
        }else if(option == "2"){
            if(root == NULL){
                std::cout << "There are no events, please add events first..." << std::endl;
            }else{
                root = add_booking(root);
                press_key();
            }
        }else if(option == "3"){
            if(root == NULL){
                std::cout << "There are no events, please add events first..." << std::endl;
            }else{
                root = cancel_booking(root);
                press_key();
            }
        }else if(option == "4"){
            list_events(root);
            press_key();
        }else if(option == "5"){
            if(root == NULL){
                std::cout << "There are no events, please add events first..." << std::endl;
            }else{
                list_specific_event(root);
                press_key();
            }
        }else if(option == "6"){
            if(root != NULL){
                std::cout << "There are events already loaded, please add clear all events first..." << std::endl;
            }else{
                root = load_from_file(root);
                press_key();
            }
        }else if(option == "7"){
            save_to_file(root);
            press_key();
        }else if(option == "8"){
            create_template();
            press_key();
        }else if (option == "9"){
            root = NULL;
            press_key();
        }else if (option == "0"){
            std::cout << "Would you like to save changes before you exit?\n(Y for Yes) " << std::endl;
            std::getline(std::cin, option);
            if(option == "Y"){
                save_to_file(root);
            }
            option = "0";
        }else{
            std::cout << "Invalid option " << option << std::endl;
            std::cout << "Please try again" << option << std::endl;
        }
    }while(option != "0");

    return 0;
 }