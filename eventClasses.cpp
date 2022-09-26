#include "eventClasses.h"

Event::Event(){
            eventName = "";
            eventDate = "";
}

Event::Event(std::string name, std::string date){
            eventName = name;
            eventDate = date;
}

//SETTERS
void Event::setName(std::string name){
    eventName = name;
}
void Event::setDate(std::string date){
    eventDate = date;
}
//GETTERS
std::string Event::getEventName() {
    return eventName;
}
std::string Event::getEventDate() {
    return eventDate;
}

int Event::countAvailableSeats() {
    int count = 0;
    for (int i=0; i < sizeof(seatsArray); i++){
        if(seatsArray[i]){
            count++;
        }
    }
    return count;
}

void Event::readEventData(){
    std::cout << "NAME: " << eventName << std::endl;
    std::cout << "DATE: " << eventDate << std::endl;
    std::cout << "AVAILABILITY: " << countAvailableSeats()
    << "/" << sizeof(seatsArray) << std::endl;
}

//Subclasses will use inherited constructor mostly
Film::Film(std::string name, std::string date, bool DFlag, int eventSeatsTaken){
    setName(name);
    setDate(date);
    is3D = DFlag;
    seatsTaken = eventSeatsTaken;
}


void Event::makeBooking(){
    if (seatsTaken >= maxAvailability){
        std::cout << "No available bookings." << std::endl;
        return;
    }
    seatsTaken = seatsTaken + 1;
    std::cout << "Booking completed." << std::endl;
}
void Event::makeBooking(int seatNumber){
    return;
}
void Film::makeBooking(){
    if (seatsTaken >= maxAvailability){
        std::cout << "No available bookings for this Film." << std::endl;
        return;
    }
    seatsTaken = seatsTaken + 1;
    std::cout << "Booking completed FILM." << std::endl;
}
void Event::removeBooking(){
    if (seatsTaken > 0){
        seatsTaken = seatsTaken - 1;
        return;
    }
    std::cout << "No seats taken, cannot remove bookings. " << std::endl;
}

void StandupComedy::makeBooking(int seatNumber){
    if(seatsArray[seatNumber]){
        std::cout << "That seat (" << seatNumber << ")is taken."
                << " Booking not completed." << std::endl;
        return;
    }
    if(seatsTaken == sizeof(seatsArray)){
        std::cout << "No available bookings." << std::endl;
    }
    seatsArray[seatNumber] = true;
    seatsTaken = seatsTaken + 1;
    std::cout << "Booking completed." << std::endl;
}

void Film::readEventData(){
    std::cout << "TYPE: Film";
    if(is3D){
        std::cout << " (3D)";
    }
    std::cout << std::endl;
    std::cout << "NAME: " << getEventName() << std::endl;
    std::cout << "DATE: " << getEventDate() << std::endl;
    std::cout << "AVAILABILITY: " << seatsTaken
    << "/" << maxAvailability << std::endl;
}

void StandupComedy::readEventData(){
    std::cout << "TYPE: Standup Comedy";
    std::cout << std::endl;
    std::cout << "NAME: " << getEventName() << std::endl;
    std::cout << "DATE: " << getEventDate() << std::endl;
    std::cout << "AVAILABILITY: " << seatsTaken
    << "/" << sizeof(seatsArray) << std::endl;
    std::cout << "SEATS TAKEN ";
    for(int i = 0; i < sizeof(seatsArray); i++){
        if(seatsArray[i]){
            std::cout << i;
            std::cout << "-";
        }
    }
    std::cout << std::endl;
}

void LiveMusic::readEventData(){
    std::cout << "TYPE: Live Music";
    std::cout << std::endl;
    std::cout << "NAME: " << getEventName() << std::endl;
    std::cout << "DATE: " << getEventDate() << std::endl;
    std::cout << "AVAILABILITY: " << seatsTaken
    << "/" << maxAvailability << std::endl;
}

LiveMusic::LiveMusic(std::string name, std::string date, int eventSeatsTaken){
    setName(name);
    setDate(date);
    seatsTaken = eventSeatsTaken;
}

StandupComedy::StandupComedy(std::string name, std::string date){
    setName(name);
    setDate(date);
}

void LiveMusic::makeBooking(){
    if (seatsTaken >= maxAvailability){
        std::cout << "No available bookings for this Live Music event." << std::endl;
        return;
    }
    seatsTaken = seatsTaken + 1;
    std::cout << "Booking completed LIVE MUSIC." << std::endl;
}

void StandupComedy::makeBooking(){
    std::string seatNumber;
    std::cout << "Please input the seat number: ";
    getline(std::cin, seatNumber);

    if(is_string_number(seatNumber)){
        if(seatsArray[std::stoi(seatNumber)]){
            std::cout << "That seat (" << seatNumber << ") is taken."
                    << " Booking not completed." << std::endl;
            return;
        }
        if(seatsTaken == sizeof(seatsArray)){
            std::cout << "No available bookings." << std::endl;
            return;
        }
        seatsArray[std::stoi(seatNumber)] = true;
        seatsTaken = seatsTaken + 1;
        std::cout << "Booking completed." << std::endl;
    }
}

void StandupComedy::removeBooking(){
    std::string seatNumber;
    std::cout << "Please input the seat number: ";
    getline(std::cin, seatNumber);

    if(is_string_number(seatNumber)){
        if(!seatsArray[std::stoi(seatNumber)]){
            std::cout << "That seat (" << seatNumber << ") is not taken."
                    << " Booking not completed." << std::endl;
            return;
        }
        if(seatsTaken == 0){
            std::cout << "No bookings, cannot remove anything." << std::endl;
            return;
        }
        seatsArray[std::stoi(seatNumber)] = false;
        seatsTaken = seatsTaken - 1;
        std::cout << "Booking removed." << std::endl;
    }
}

void LiveMusic::removeBooking(){
    if (seatsTaken == 0){
        std::cout << "No bookings, cannot remove anything" << std::endl;
        return;
    }
    seatsTaken = seatsTaken - 1;
    std::cout << "Booking removed." << std::endl;
}

void Film::removeBooking(){
    if (seatsTaken == 0){
        std::cout << "No bookings, cannot remove anything" << std::endl;
        return;
    }
    seatsTaken = seatsTaken - 1;
    std::cout << "Booking removed." << std::endl;
}

std::string Film::saveEventDataString(){
    std::string result = "";

    result = result + getEventName();
    result = result + ", " + getEventDate();
    if(is3D){
        result = result + ", " + "F3D";
    }else{
        result = result + ", " + "F2D";
    }
    result = result + ", " + std::to_string(maxAvailability);
    result = result + "\n";

    return result;
}

std::string StandupComedy::saveEventDataString(){
    std::string result = "";

    result = result + getEventName();
    result = result + ", " + getEventDate();
    result = result + ", " + "SC";
    result = result + ", " + std::to_string(sizeof(seatsArray));
    result = result + ", ";
    for(int i = 0; i < sizeof(seatsArray); i++){
        if(seatsArray[i]) result = result + std::to_string(i) + "-";
    }
    result = result + "\n";

    return result;
}

std::string LiveMusic::saveEventDataString(){
    std::string result = "";

    result = result + getEventName();
    result = result + ", " + getEventDate();
    result = result + ", " + "LM";
    result = result + ", " + std::to_string(maxAvailability);
    result = result + "\n";

    return result;
}


std::string Event::saveEventDataString(){
    return "";
}