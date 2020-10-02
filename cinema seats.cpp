#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex> 
using namespace std;

vector<string> splitByChar(const string& str, const char& ch) {
	vector<string> out_arr;
	int out_arr_n;
	string working_str = str;
	
	out_arr_n = std::count(working_str.begin(), working_str.end(), ch) + 1;
	out_arr.resize(out_arr_n);
	
	size_t pos = 0;
    string token;
	int i = 0;
    while ((pos = working_str.find(ch)) != string::npos) {
        token = working_str.substr(0, pos);
		
		out_arr[i] = token;
		i++;
        working_str.erase(0, pos + 1);
    }
	
	if (working_str.length()) out_arr[i] = working_str;
	
	return out_arr;
}

class House {
	public:
	    string house_path;
		int price_f;           
		int price_h;           
		int price_e;          
		int nrow;
		int ncol;
		bool good;
		std::vector<int> all_seats;
		
		void showHelp();
		void setHouse(string house_full_path);
		void showSeats();
		void buyTickets();
		void cancelBooking();
		void updateSeats();
		void totalProfit();
		
	private:
	    bool checkSeatsPattern(string seats);
		int getPrice(int row, int col);
};

bool House::checkSeatsPattern(string seats) {
	regex pattern ("([A-Z][0-9]{1,2},)*[A-Z][0-9]{1,2}");
	bool check_result = true;
	
	if (!regex_match(seats, pattern)) {
		cout << "The seats entered are in wrong pattern." << endl;
		cout << "Valid pattern is in format A1,B2,C4 etc." << endl;
		check_result = false;
	}
	
	return check_result;
}

int House::getPrice(int row, int col) {
	return all_seats[row * ncol + col];
}

void House::showHelp() {
	cout << "b - buy tickets, f = full price, h = half price, e = elderly price" << endl;
	cout << "c - cancel booking" << endl;
	cout << "h - show this help" << endl;
	cout << "q - quit" << endl;
	cout << "s - show seats" << endl;
	cout << "t - display total profit" << endl;
}

void House::setHouse(string house_full_path) {
	house_path = house_full_path;
	
	price_f = 100;
	price_h = price_f / 2;
	price_e = 20;
	
	nrow = 1;
	ncol = 0;
	good = true;
	
	ifstream file;
	
	file.open(house_path);
	if (file.good()) {
		// Count number of tabs in first line in txt to determine number
		// of columns in house
		string firstRow;
		std::getline(file, firstRow);
		ncol = std::count(firstRow.begin(), firstRow.end(), '\t');
		ncol++;                    // Number of tabs + 1 = number of columns
		
		// Count number of lines in txt to determine number of rows in house
		string thisRow;
		while (std::getline(file, thisRow)) {
			nrow++;
		}
	} else good = false;
	file.close();
	
	// Only support house of size less than or equal to 26 x 9
	if (good) {
		if (nrow > 26) {
			cout << "This house has too many rows." << endl;
			good = false;
		} else if (ncol > 9) {
			cout << "This house has too many columns." << endl;
			good = false;
		}
	}
	
	if (good) {
		// Get seat info in house from txt
		all_seats.resize(nrow * ncol);
		
		file.open(house_path);
		for (int row=0; row<nrow; row++) {
			for (int col=0; col<ncol; col++) {
				file >> all_seats[row * ncol + col];
			}
		}
		file.close();
	}
}

void House::showSeats() {
	char row_chr;
	char out_chr;
	
	
	cout << "O: available, X: sold" << endl << endl;
	cout << string(8, ' ') << string(2 * (ncol - 1) + 1, '-') << "SCREEN" << string(2 * (ncol - 1), '-') << endl;
	
	
	cout << string(8, ' ');
	for (int col=0; col<ncol; col++) {
		cout << string(3, ' ') << col + 1;
	}
	cout << endl;
	
	for (int row=0; row<nrow; row++) {
	
		row_chr = row + 65;
		
		cout << string(5, ' ') << row_chr << " |" << string(3, ' ');
		for (int col=0; col<ncol; col++) {
			
			if (all_seats[row * ncol + col] > 0) {
				out_chr = 'X';
			} else if (all_seats[row * ncol + col] == 0) {
				out_chr = 'O';
			} else out_chr = ' ';
			
			cout << out_chr << string(3, ' ');
		}
		
		
		cout << "| " << row_chr << endl;
	}
}


void House::buyTickets() {
	string seats;
	int nseats;
	int price;
	string price_option, confirm;
	
	cout << "Buy tickets" << endl << "Please enter seats in A1,B2,C4 etc." << endl;
	
	cin >> seats;
	

	if (!checkSeatsPattern(seats)) return;
	
	std::vector<string> seats2Buy = splitByChar(seats, ',');
	nseats = seats2Buy.size();
	
	for (int i=0; i<nseats; i++) {
		int row = int(seats2Buy[i].at(0)) - 65;                                        
		int col = std::stoi(seats2Buy[i].substr(1, seats2Buy[i].length() - 1)) - 1;    
		
		if (row + 1 > nrow || col + 1 > ncol) {
			cout << seats2Buy[i] << ": Seat out of seatplan, please check again" << endl;
			continue;
		} else if (all_seats[row * ncol + col] == -1) {
			cout << seats2Buy[i] << ": Seat is not available" << endl;
			continue;
		} else if (all_seats[row * ncol + col] > 0) {
			cout << seats2Buy[i] << ": Seat already sold" << endl;
			continue;
		} else {
		
			cout << "Buy " << seats2Buy[i] << " - price option (f/h/e):" << endl;
			
			while (true) {
				cin >> price_option;
				
				if (price_option == "f") {
					price = price_f;
				} else if (price_option == "h") {
					price = price_h;
				} else if (price_option == "e") {
					price = price_e;
				} else {
					cout << "No such option, please try again" << endl;
					continue;
				}
				
		
				cout << "Buy " << seats2Buy[i] << " at " << price << ", y to confirm, n to cancel" << endl;
			
				while (true) {
					cin >> confirm;
					
					if (confirm == "y") {
						all_seats[row * ncol + col] = price;
						break;
					} else if (confirm != "n") {
						cout << "No such option, please try again" << endl;
					} else break;
				}
				
				if (confirm == "y" | confirm == "n") break;
			}
		}
	}
	

	updateSeats();
}

void House::cancelBooking() {
	string seats;
	int nseats;
	
	cout << "Cancel booking" << endl << "Please enter seats in A1,B2,C4 etc." << endl;
	
	cin >> seats;
	

	if (!checkSeatsPattern(seats)) return;
	
	std::vector<string> seats2Buy = splitByChar(seats, ',');
	nseats = seats2Buy.size();
	
	for (int i=0; i<nseats; i++) {
		int row = int(seats2Buy[i].at(0)) - 65;                                        // First character as row
		int col = std::stoi(seats2Buy[i].substr(1, seats2Buy[i].length() - 1)) - 1;    // Remaining characters as col
		
		if (row + 1 > nrow || col + 1 > ncol) {
			cout << seats2Buy[i] << ": Seat out of seatplan, please check again" << endl;
			continue;
		} else if (all_seats[row * ncol + col] == -1) {
			cout << seats2Buy[i] << ": Seat is not available" << endl;
			continue;
		} else if (all_seats[row * ncol + col] == 0) {
			cout << seats2Buy[i] << ": Seat has not been sold" << endl;
			continue;
		} else {
			all_seats[row * ncol + col] = 0;
		}
	}
	

	updateSeats();
}

void House::updateSeats() {
	ofstream file;
	
	file.open(house_path);
	for (int row=0; row<nrow; row++) {
		for (int col=0; col<ncol; col++) {
			file << all_seats[row * ncol + col];
			if (col + 1 != ncol) file << '\t';
		}
		file << endl;
	}
	
	file.close();
}

void House::totalProfit() {
	int total_profit = 0;
	
	for (int row=0; row<nrow; row++) {
		for (int col=0; col<ncol; col++) {
			if (getPrice(row, col) > 0) total_profit += getPrice(row, col);
		}
	}
	
	cout << "Total profit is " << total_profit << "." << endl;
}

int main() {
	House house;
	string house_path, action;
	
	cout << "Please input txt file name for house: " << endl;
	cin >> house_path;
	

	house.setHouse(house_path);
	
	if (house.good) {
		while (true) {
			cout << "How can I help you? (h for help)" << endl;
			cin >> action;
			
			if (action == "h") {
				house.showHelp();
			} else if (action == "s") {
				house.showSeats();
			} else if (action == "b") {
				house.buyTickets();
			} else if (action == "c") {
				house.cancelBooking();
			} else if (action == "t") {
				house.totalProfit();
			} else if (action == "q") {
				break;
			} else {
				cout << "No such action, please try again!" << endl;
			}
		}
	} else {
		cout << "Error when initializing house, please check the txt file" << endl;
	}
	
	return 0;
}
