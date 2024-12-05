#include "BookFlix.h"
#include <iostream>

using namespace std;

int main(){
    string filename = "kindle_data-v2.csv";
    vector<string> books;
    vector<Book> compBooks;
    Book book(filename, books);
    book.preprocessFile();

    bool running = true;

    while (running) {
        cout << "Welcome to BOOKFLIX!" << endl;
        cout << "===========================" << endl;
        cout << "Would you like to see our top-rated books? (y/n)" << endl;
        string answer;
        cin >> answer;

        if (answer == "y" || answer == "Y") {
            // Call heap() to sort the books and display them
            book.heap();

            vector<Book> sortedBooks;
            for (const auto& [id, bk] : book.database) {
                sortedBooks.push_back(bk);
            }

            // Display sorted books
            cout << "\nTop-Rated Books:\n";
            int counter = 1;
            for (const auto& b : sortedBooks) {
                cout << "Title: " << b.getBooktitle()
                     << " | Rating: " << b.getRating()
                     << " | Author: " << b.getBookAuthor()
                     << " | Price: " << b.getBookPrice() << endl;
                counter ++;
                if (counter >= 11){
                    break;
                }
            }
        }
        book.welcomeScreen();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                // Implement book search functionality here
               book.search();
                break;
            case 2:
                book.takeQuiz();
                break;
            case 3:
                running = false;
                break;
            case 4:
                cout << "Goodbye!" << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
    return 0;
}

