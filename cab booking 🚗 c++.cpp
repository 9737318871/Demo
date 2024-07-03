#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Cab {
    int cabId;
    string driverName;
    string carModel;
    int availableSeats;
    float farePerKilometer;
    string contactNumber;
};

struct Booking {
    int bookingId;
    int cabId;
    string customerName;
    string pickupLocation;
    string dropLocation;
    float distance;
    float totalFare;
};

// Function to display available cabs
void displayCabs(Cab cabs[], int numCabs) {
    cout << "Available Cabs:\n";
    for (int i = 0; i < numCabs; i++) {
        if (cabs[i].availableSeats > 0) {
            cout << "Cab ID: " << cabs[i].cabId << endl;
            cout << "Driver Name: " << cabs[i].driverName << endl;
            cout << "Car Model: " << cabs[i].carModel << endl;
            cout << "Available Seats: " << cabs[i].availableSeats << endl;
            cout << "Fare per Kilometer: " << cabs[i].farePerKilometer << endl;
            cout << "Contact Number: " << cabs[i].contactNumber << endl << endl;
        }
    }
}

// Function to book a cab
void bookCab(Cab cabs[], int numCabs, Booking bookings[], int& numBookings) {
    int cabId;
    float distance;
    string customerName, pickupLocation, dropLocation;

    cout << "Enter your name: ";
    cin >> customerName;
    cout << "Enter pickup location: ";
    cin >> pickupLocation;
    cout << "Enter drop location: ";
    cin >> dropLocation;
    cout << "Enter the distance to your destination (in km): ";
    cin >> distance;
    
    // Display available cabs
    displayCabs(cabs, numCabs);
    
    cout << "Enter the Cab ID you want to book: ";
    cin >> cabId;
    
    // Check if the selected cab is available
    if (cabId < 1 || cabId > numCabs || cabs[cabId - 1].availableSeats <= 0) {
        cout << "Invalid cab selection or cab not available." << endl;
        return;
    }
    
    // Calculate the total fare
    float totalFare = distance * cabs[cabId - 1].farePerKilometer;
    
    // Book the cab
    Booking booking;
    booking.bookingId = numBookings + 1;
    booking.cabId = cabId;
    booking.customerName = customerName;
    booking.pickupLocation = pickupLocation;
    booking.dropLocation = dropLocation;
    booking.distance = distance;
    booking.totalFare = totalFare;
    
    // Update the cab's availability
    cabs[cabId - 1].availableSeats--;
    
    // Add the booking to the list
    bookings[numBookings++] = booking;
    
    cout << "Cab booked successfully. Booking ID: " << numBookings << endl;
}

// Function to view and save booking details
void viewAndSaveBookings(Booking bookings[], int numBookings) {
    ofstream file("bookings.txt");
    if (!file.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    cout << "Booking Details:" << endl;
    cout << "----------------------------" << endl;

    for (int i = 0; i < numBookings; i++) {
        cout << "Booking ID: " << bookings[i].bookingId << endl;
        cout << "Customer Name: " << bookings[i].customerName << endl;
        cout << "Pickup Location: " << bookings[i].pickupLocation << endl;
        cout << "Drop Location: " << bookings[i].dropLocation << endl;
        cout << "Distance: " << bookings[i].distance << " km" << endl;
        cout << "Total Fare: $" << bookings[i].totalFare << endl;
        cout << "----------------------------" << endl;

        // Save the booking details to a text file
        file << "Booking ID: " << bookings[i].bookingId << endl;
        file << "Customer Name: " << bookings[i].customerName << endl;
        file << "Pickup Location: " << bookings[i].pickupLocation << endl;
        file << "Drop Location: " << bookings[i].dropLocation << endl;
        file << "Distance: " << bookings[i].distance << " km" << endl;
        file << "Total Fare: $" << bookings[i].totalFare << endl;
        file << "----------------------------" << endl;
    }

    file.close();
    cout << "Booking details saved to 'bookings.txt'." << endl;
}

int main() {
    // Initialize cabs and bookings
    Cab cabs[5]; // Assuming 5 cabs
    Booking bookings[100]; // Assuming a maximum of 100 bookings
    int numCabs = 5;
    int numBookings = 0;
    
    // Initialize cabs with some data
    for (int i = 0; i < numCabs; i++) {
        cabs[i].cabId = i + 1;
        cabs[i].driverName = "Driver" + to_string(i + 1);
        cabs[i].carModel = "CarModel" + to_string(i + 1);
        cabs[i].availableSeats = 4;
        cabs[i].farePerKilometer = 5.0 + i;
        cabs[i].contactNumber = "123-456-" + to_string(i + 1);
    }
    
    int choice;
    
    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Book a cab" << endl;
        cout << "2. View and Save Booking Details" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                bookCab(cabs, numCabs, bookings, numBookings);
                break;
            case 2:
                viewAndSaveBookings(bookings, numBookings);
                break;
            case 3:
                cout << "Thank you for using the cab booking system." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    
    return 0;
}
