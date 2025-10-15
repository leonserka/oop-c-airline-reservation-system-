#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <regex>
#include <algorithm>
#include <unordered_set>

using namespace std;

// Helper function to validate email format
bool isValidEmail(const std::string& email) {
    const std::regex emailPattern(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    return std::regex_match(email, emailPattern);
}

// Base Flight class implementing abstraction
class Flight {
protected:
    std::string departureCity, arrivalCity, departureTime, arrivalTime, date, flightNumber;
    double price;
    int totalSeats, baggageAllowance;

public:
    virtual ~Flight() = default;

    // Virtual method for displaying flight details
    virtual void displayFlightDetails() const = 0;

    void setFlightDetails(const std::string& depCity, const std::string& arrCity, const std::string& depTime,
                          const std::string& arrTime, const std::string& date, double price, const std::string& flightNum,
                          int totalSeats, int baggageAllowance) {
        this->departureCity = depCity;
        this->arrivalCity = arrCity;
        this->departureTime = depTime;
        this->arrivalTime = arrTime;
        this->date = date;
        this->price = price;
        this->flightNumber = flightNum;
        this->totalSeats = totalSeats;
        this->baggageAllowance = baggageAllowance;
    }

    int getAvailableSeats() const { return totalSeats; }
    void reduceAvailableSeats() { if (totalSeats > 0) totalSeats--; }
};

// Domestic Flight class
class DomesticFlight : public Flight {
public:
    DomesticFlight(const std::string& depCity, const std::string& arrCity, const std::string& depTime,
                   const std::string& arrTime, const std::string& date, double price, const std::string& flightNum,
                   int totalSeats, int baggageAllowance) {
        setFlightDetails(depCity, arrCity, depTime, arrTime, date, price, flightNum, totalSeats, baggageAllowance);
    }

    void displayFlightDetails() const override {
        std::cout << "Domestic Flight: " << flightNumber << "\n"
                  << "Departure: " << departureCity << " at " << departureTime << "\n"
                  << "Arrival: " << arrivalCity << " at " << arrivalTime << "\n"
                  << "Date: " << date << ", Price: $" << price << "\n"
                  << "Seats Available: " << totalSeats << ", Baggage Allowance: " << baggageAllowance << "kg\n";
    }
};

// International Flight class
class InternationalFlight : public Flight {
public:
    InternationalFlight(const std::string& depCity, const std::string& arrCity, const std::string& depTime,
                        const std::string& arrTime, const std::string& date, double price, const std::string& flightNum,
                        int totalSeats, int baggageAllowance) {
        setFlightDetails(depCity, arrCity, depTime, arrTime, date, price, flightNum, totalSeats, baggageAllowance);
    }

    void displayFlightDetails() const override {
        std::cout << "International Flight: " << flightNumber << "\n"
                  << "Departure: " << departureCity << " at " << departureTime << "\n"
                  << "Arrival: " << arrivalCity << " at " << arrivalTime << "\n"
                  << "Date: " << date << ", Price: $" << price << "\n"
                  << "Seats Available: " << totalSeats << ", Baggage Allowance: " << baggageAllowance << "kg\n";
    }
};

// Ticket class
class Ticket {
private:
    std::shared_ptr<Flight> flight;
    std::string passengerName, passengerSurname, idNumber, email, phoneNumber, paymentMethod, seatClass;

public:
    Ticket(const std::shared_ptr<Flight>& flight) : flight(flight) {}

    void setPassengerDetails(const std::string& name, const std::string& surname, const std::string& id,
                             const std::string& email, const std::string& phone, const std::string& payment, const std::string& seatClass) {
        this->passengerName = name;
        this->passengerSurname = surname;
        this->idNumber = id;
        this->email = email;
        this->phoneNumber = phone;
        this->paymentMethod = payment;
        this->seatClass = seatClass;
    }

    void displayTicketDetails() const {
        std::cout << "Passenger: " << passengerName << " " << passengerSurname << "\n"
                  << "ID: " << idNumber << ", Email: " << email << ", Phone: " << phoneNumber << "\n"
                  << "Payment Method: " << paymentMethod << ", Seat Class: " << seatClass << "\n";
        flight->displayFlightDetails();
    }

    const std::string& getIDNumber() const { return idNumber; }
};

// Booking System class
class BookingSystem {
private:
    std::vector<std::shared_ptr<Ticket>> bookedTickets;

public:
    void bookFlight(const std::shared_ptr<Flight>& flight, const std::string& name, const std::string& surname,
                    const std::string& id, const std::string& email, const std::string& phone, const std::string& payment,
                    const std::string& seatClass) {
        if (flight->getAvailableSeats() <= 0) {
            std::cout << "No seats available for this flight!\n";
            return;
        }

        flight->reduceAvailableSeats();
        std::shared_ptr<Ticket> ticket = std::make_shared<Ticket>(flight);
        ticket->setPassengerDetails(name, surname, id, email, phone, payment, seatClass);
        bookedTickets.push_back(ticket);
        std::cout << "Flight booked successfully!\n";
        ticket->displayTicketDetails();
    }

    void cancelFlight(const std::string& id) {
        auto it = std::remove_if(bookedTickets.begin(), bookedTickets.end(),
                                 [&id](const std::shared_ptr<Ticket>& ticket) { return ticket->getIDNumber() == id; });

        if (it != bookedTickets.end()) {
            bookedTickets.erase(it, bookedTickets.end());
            std::cout << "Flight canceled successfully!\n";
        } else {
            std::cout << "No booking found with the provided ID.\n";
        }
    }

    void viewBookedFlights() const {
        if (bookedTickets.empty()) {
            std::cout << "No booked flights available.\n";
            return;
        }

        for (const auto& ticket : bookedTickets) {
            ticket->displayTicketDetails();
            std::cout << "---------------------------------\n";
        }
    }

    void checkTicket(const std::string& id) const {
        for (const auto& ticket : bookedTickets) {
            if (ticket->getIDNumber() == id) {
                ticket->displayTicketDetails();
                return;
            }
        }
        std::cout << "No ticket found with the provided ID.\n";
    }
};

// Helper function for creating flights
std::shared_ptr<Flight> createFlight(int flightType) {
    std::unordered_set<std::string> domesticCities = {"Zagreb", "Split", "Rijeka", "Dubrovnik", "Zadar"};
    std::unordered_set<std::string> internationalCities = {"Amsterdam", "Bec", "Bruxelles", "Frankfurt", "Kopenhagen",
                                                           "London", "Mostar", "München", "Pariz", "Rim",
                                                           "Sarajevo", "Zürich"};
    std::string depCity, arrCity, depTime, arrTime, date, flightNum;
    double price;
    int totalSeats, baggageAllowance;

    if (flightType == 1) {
        do {
            std::cout << "Enter Departure City (Zagreb, Split, Rijeka, Dubrovnik, Zadar): ";
            std::cin >> depCity;
            if (domesticCities.find(depCity) == domesticCities.end()) {
                std::cout << "Invalid city. Please select a valid domestic city.\n";
            }
        } while (domesticCities.find(depCity) == domesticCities.end());

        do {
            std::cout << "Enter Arrival City (Zagreb, Split, Rijeka, Dubrovnik, Zadar): ";
            std::cin >> arrCity;
            if (domesticCities.find(arrCity) == domesticCities.end()) {
                std::cout << "Invalid city. Please select a valid domestic city.\n";
            }
        } while (domesticCities.find(arrCity) == domesticCities.end());
    } else {
        do {
            std::cout << "Enter Departure City (Amsterdam, Bec, Bruxelles, Frankfurt, Kopenhagen, London, Mostar, "
                         "München, Pariz, Rim, Sarajevo, Zürich): ";
            std::cin >> depCity;
            if (internationalCities.find(depCity) == internationalCities.end()) {
                std::cout << "Invalid city. Please select a valid international city.\n";
            }
        } while (internationalCities.find(depCity) == internationalCities.end());

        do {
            std::cout << "Enter Arrival City (Amsterdam, Bec, Bruxelles, Frankfurt, Kopenhagen, London, Mostar, "
                         "München, Pariz, Rim, Sarajevo, Zürich): ";
            std::cin >> arrCity;
            if (internationalCities.find(arrCity) == internationalCities.end()) {
                std::cout << "Invalid city. Please select a valid international city.\n";
            }
        } while (internationalCities.find(arrCity) == internationalCities.end());
    }

    std::cout << "Enter Departure Time (HH:MM): ";
    std::cin >> depTime;
    std::cout << "Enter Arrival Time (HH:MM): ";
    std::cin >> arrTime;
    std::cout << "Enter Date (DD/MM/YYYY): ";
    std::cin >> date;
    std::cout << "Enter Price: ";
    std::cin >> price;
    std::cout << "Enter Flight Number: ";
    std::cin >> flightNum;
    std::cout << "Enter Total Seats: ";
    std::cin >> totalSeats;
    std::cout << "Enter Baggage Allowance (kg): ";
    std::cin >> baggageAllowance;

    if (flightType == 1) {
        return make_shared<DomesticFlight>(depCity, arrCity, depTime, arrTime, date, price, flightNum, totalSeats, baggageAllowance);
    } else {
        return make_shared<InternationalFlight>(depCity, arrCity, depTime, arrTime, date, price, flightNum, totalSeats, baggageAllowance);
    }
}

int main() {
    BookingSystem bookingSystem;
    std::vector<std::shared_ptr<Flight>> flights;
    std::vector<std::shared_ptr<BookingSystem>> Tickets;
    

    int choice;
    do {
        std::cout << "\n=== Airline Reservation System ===\n";
        std::cout << "1. Create Domestic Flight\n";
        std::cout << "2. Create International Flight\n";
        std::cout << "3. Book a Flight\n";
        std::cout << "4. Cancel a Flight\n";
        std::cout << "5. View Booked Flights\n";
        std::cout << "6. Check Ticket by ID\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
            case 2: {
                auto flight = createFlight(choice);
                flights.push_back(flight);
                std::cout << "Flight created successfully!\n";
                break;
            }
            case 3: {
                if (flights.empty()) {
                    std::cout << "No flights available for booking.\n";
                    break;
                }

                std::cout << "Available Flights:\n";
                for (size_t i = 0; i < flights.size(); ++i) {
                    std::cout << i + 1 << ". ";
                    flights[i]->displayFlightDetails();
                }

                size_t flightIndex;
                std::cout << "Enter the flight number to book: ";
                std::cin >> flightIndex;

                if (flightIndex < 1 || flightIndex > flights.size()) {
                    std::cout << "Invalid flight selection.\n";
                    break;
                }

                std::string name, surname, id, email, phone, payment, seatClass;
                std::cout << "Enter Passenger Name: ";
                std::cin >> name;
                std::cout << "Enter Passenger Surname: ";
                std::cin >> surname;
                std::cout << "Enter ID Number: ";
                std::cin >> id;

                // Validate email input
                std::cout << "Enter Email: ";
                std::cin >> email;
                while (!isValidEmail(email)) {
                    std::cout << "Invalid email format. Please enter a valid email: ";
                    std::cin >> email;
                }

                std::cout << "Enter Phone Number: ";
                std::cin >> phone;
                std::cout << "Enter Payment Method: ";
                std::cin >> payment;
                std::cout << "Enter Seat Class (Economy/Business): ";
                std::cin >> seatClass;

                bookingSystem.bookFlight(flights[flightIndex - 1], name, surname, id, email, phone, payment, seatClass);
                break;
            }
            case 4: {
                if (flights.empty()) {
                    std::cout << "No flights available.\n";
                    break;
                }
                std::string id;
                std::cout << "Enter ID Number to cancel the flight: ";
                std::cin >> id;
                bookingSystem.cancelFlight(id);
                break;
            }
            case 5:
                bookingSystem.viewBookedFlights();
                break;
            case 6: {
                std::string id;
                std::cout << "Enter ID Number to check the ticket: ";
                std::cin >> id;
                bookingSystem.checkTicket(id);
                break;
            }
            case 7:
                std::cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 7);

    return 0;
}
