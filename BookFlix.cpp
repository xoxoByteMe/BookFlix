#include "BookFlix.h"

Book::Book(const string& filename, const vector<string>& books)
        : filename(filename), books(books) {
}

void Book::welcomeScreen() {
    cout << "=========================================" << endl;
    cout << "   Welcome to BookFlix!" << endl;
    cout << "   An app for searching all your favorite books." << endl;
    cout << "=========================================" << endl;
    cout << "Please choose an option:" << endl;
    cout << "1. Search for a book" << endl;
    cout << "2. Take the quiz to find matching books" << endl;
    cout << "3. Exit" << endl;
    cout << "=========================================" << endl;
}

string Book::formatBookDetails() const {
    return "\nASIN: " + asin + "\n" +
           "Title: " + title + "\n" +
           "Author: " + author + "\n" +
           "Sold By: " + soldBy + "\n" +
           "Image URL: " + imgUrl + "\n" +
           "Product URL: " + productURL + "\n" +
           "Stars: " + stars + "\n" +
           "Reviews: " + reviews + "\n" +
           "Price: " + price + "\n" +
           "Kindle Unlimited: " + (isKindleUnlimited ? "Yes" : "No") + "\n" +
           "Category ID: " + category_id + "\n" +
           "Best Seller: " + (isBestSeller ? "Yes" : "No") + "\n" +
           "Editor's Pick: " + (isEditorsPick ? "Yes" : "No") + "\n" +
           "Goodreads Choice: " + (isGoodReadsChoice ? "Yes" : "No") + "\n" +
           "Published Date: " + publishedDate + "\n" +
           "Category Name: " + category_name + "\n";
}

void Book::preprocessFile() {
    ifstream file(filename);

    if (file.is_open()) {
        cout << "Preprocessing file: " << filename << endl;
        string line;

        // Skip the header line
        getline(file, line);


        int count = 0;

        while (getline(file, line)) {
            vector<string> fields;
            string field;
            bool insideQuotes = false;

            // Parse line manually, handling quotes
            for (char c : line) {
                if (c == '"') {
                    insideQuotes = !insideQuotes; // Toggle inside/outside quotes
                }
                else if (c == ',' && !insideQuotes) {
                    fields.push_back(field); // Add the completed field
                    field.clear();
                }
                else {
                    field += c;
                }
            }
            fields.push_back(field); // Add the last field

            // Ensure we have the correct number of fields
            if (fields.size() < 16) {
                cerr << "Error parsing line: Missing fields" << endl;
                continue;
            }

            asin = fields[0];
            title = fields[1];
            author = fields[2];
            soldBy = fields[3];
            imgUrl = fields[4];
            productURL = fields[5];
            stars = fields[6];
            reviews = fields[7];
            price = fields[8];
            isKindleUnlimited = (fields[9] == "True");
            category_id = fields[10];
            isBestSeller = (fields[11] == "True");
            isEditorsPick = (fields[12] == "True");
            isGoodReadsChoice = (fields[13] == "True");
            publishedDate = fields[14];
            category_name = fields[15];



            // sets for the quiz
            uniqueGenres.insert(category_name);
            isUnlimited.push_back(isKindleUnlimited);
            editorsPick.push_back(isEditorsPick);
            goodReads.push_back(isGoodReadsChoice);
            bestSeller.push_back(isBestSeller);
            titleSet.push_back(title);

            try {
                starsNum.push_back(stod(stars));
                priceNum.push_back(stod(price));
                reviewNum.push_back(stoi(reviews));
            }
            catch (const invalid_argument& e) {
                cerr << "Error converting to double: " << e.what() << endl;
            }

            //booksInMemory.push_back(formatBookDetails());

            Book newBook(filename, books);  // You can pass any parameters necessary to construct a Book
            newBook.asin = asin;
            newBook.title = title;
            newBook.author = author;
            newBook.soldBy = soldBy;
            newBook.imgUrl = imgUrl;
            newBook.productURL = productURL;
            newBook.stars = stars;
            newBook.reviews = reviews;
            newBook.price = price;
            newBook.isKindleUnlimited = isKindleUnlimited;
            newBook.category_id = category_id;
            newBook.isBestSeller = isBestSeller;
            newBook.isEditorsPick = isEditorsPick;
            newBook.isGoodReadsChoice = isGoodReadsChoice;
            newBook.publishedDate = publishedDate;
            newBook.category_name = category_name;

            // Add the Book object to booksInMemory
            booksInMemory.push_back(newBook);

            // populate database

            addBook(newBook);
            count++;

        }
        cout << "Preprocessing done." << endl;


        file.close();

        if (booksInMemory.empty()) {
            cout << "Empty Memory." << endl;
        }

    }
    else {
        cerr << "File failed to open: " << filename << endl;
    }
}




// FUNCTIONS FOR GETTING EVERYTHING

vector<double> Book::getPriceNum() const {
    return priceNum;  // Return prices in order
}

vector<double> Book::getStarsNum() const {
    return starsNum;  // Return star ratings in order
}

set<string> Book::getUniqueGenres() const {
    return uniqueGenres;
}

vector<string> Book::getTitle() const {
    return titleSet;  // Return titles in order
}

vector<bool> Book::getIsUnlimited() const {
    return isUnlimited;  // Return Kindle Unlimited statuses in order
}

vector<bool> Book::getEditorsPick() const {
    return editorsPick;  // Return Editor's Pick statuses in order
}

vector<bool> Book::getGoodReads() const {
    return goodReads;  // Return Goodreads Choice statuses in order
}

vector<bool> Book::getBestSeller() const {
    return bestSeller;  // Return Best Seller statuses in order
}

vector<int> Book::getReviewNum() const {
    return reviewNum;  // Return review numbers in order
}

vector<Book> Book::getBooksInMemory() {
    return booksInMemory;
}


pair<double, double> getPriceRange() {
    while (true) {
        cout << "Enter your preferred price range (min-max): ";
        string input;
        cin >> input;

        size_t hyphen = input.find('-');
        if (hyphen == string::npos) {
            cout << "Invalid format. Please use min-max (e.g., 5-20)." << endl;
            continue;
        }

        try {
            double minPrice = stod(input.substr(0, hyphen));
            double maxPrice = stod(input.substr(hyphen + 1));
            if (minPrice > maxPrice) {
                cout << "Invalid range. Minimum price must be less than or equal to maximum price." << endl;
                continue;
            }
            return { minPrice, maxPrice };
        }
        catch (const invalid_argument&) {
            cout << "Invalid numbers. Please re-enter." << endl;
        }
    }
}


set<string> getGenrePreferences(const set<string>& availableGenres) {
    cout << "Available Genres:" << endl;
    vector<string> genresList(availableGenres.begin(), availableGenres.end());
    int count = 1;
    for (const string& genre : genresList) {
        cout << count << ". " << genre << endl;
        count++;
    }
    cout << endl;

    cout << "Enter your preferred genres by number (e.g., 1 2 5 or 1,2,5): ";
    set<string> selectedGenres;
    string input;
    cin >> input;
//    cin.ignore();
    getline(cin, input);

    istringstream iss(input);
    string token;
    while (iss >> token) {
        if (token.back() == ',') token.pop_back();  // Remove trailing comma
        try {
            int index = stoi(token);
            if (index >= 1 && index <= genresList.size()) {
                selectedGenres.insert(genresList[index - 1]);
            }
            else {
                cout << "Invalid genre number: " << index << ". Skipping." << endl;
            }
        }
        catch (const invalid_argument&) {
            cout << "Invalid input: " << token << ". Skipping." << endl;
        }
    }
    return selectedGenres;
}

pair<int, int> getReviewRange() {
    while (true) {
        cout << "Enter your preferred review range (min-max, whole numbers only): ";
        string input;
        cin >> input;

        size_t hyphen = input.find('-');
        if (hyphen == string::npos) {
            cout << "Invalid format. Please use min-max (e.g., 10-100)." << endl;
            continue;
        }

        try {
            int minReviews = stoi(input.substr(0, hyphen));
            int maxReviews = stoi(input.substr(hyphen + 1));
            if (minReviews > maxReviews) {
                cout << "Invalid range. Minimum reviews must be less than or equal to maximum reviews." << endl;
                continue;
            }
            return { minReviews, maxReviews };
        }
        catch (const invalid_argument&) {
            cout << "Invalid numbers. Please re-enter." << endl;
        }
    }
}

bool getBooleanPreference(const string& question) {
    while (true) {
        cout << question << " (yes/y or no/n): ";
        string input;
        cin >> input;

        if (input == "yes" || input == "y") {
            return true;
        }
        else if (input == "no" || input == "n") {
            return false;
        }
        else {
            cout << "Invalid input. Please answer yes/y or no/n." << endl;
        }
    }
}



// Updated getCompatibleBooks function
set<string> Book::getCompatibleBooks(
        vector<Book>& booksInMemoryParam,
        pair<double, double>& priceRangeParam,
        const set<string>& preferredGenresParam,
        const pair<int, int>& reviewRangeParam,
        bool kindleUnlimitedParam,
        bool editorsPickParam,
        bool bestSellerParam,
        bool goodReadsChoiceParam
) {
    set<string> compatibleBooks;  // Set to store the compatible books

    // Assuming getBooksInMemory() is a member function
    booksInMemoryParam = getBooksInMemory();
    //priceRangeParam = getPriceRange();

    // Iterate over all the books in memory
    for (const auto& book : booksInMemoryParam) {
        int criteriaMatchCount = 0;  // To count how many criteria match

        // Check price range
        try{
            double bkPrice = stod(book.price);
            if (bkPrice > priceRangeParam.first && bkPrice <= priceRangeParam.second) {
                criteriaMatchCount++;
            }
        }
        catch (const invalid_argument&){
            cout << "invalid price" << endl;
        }

        // Check genre preference
        if (preferredGenresParam.find(book.category_name) != preferredGenresParam.end()) {
            criteriaMatchCount++;
        }

        // Check review range
        try{
            int bkReview = stoi(book.reviews);
            if (bkReview >= reviewRangeParam.first && bkReview <= reviewRangeParam.second){
                criteriaMatchCount++;
            }
        }
        catch (const invalid_argument&){
            cout << "invalid review range" << endl;
        }

        // Check Kindle Unlimited preference
        if (book.isKindleUnlimited == kindleUnlimitedParam) {
            criteriaMatchCount++;
        }

        // Check Editor's Pick preference
        if (book.isEditorsPick == editorsPickParam) {
            criteriaMatchCount++;
        }

        // Check Best Seller preference
        if (book.isBestSeller == bestSellerParam) {
            criteriaMatchCount++;
        }

        // Check Goodreads Choice preference
        if (book.isGoodReadsChoice == goodReadsChoiceParam) {
            criteriaMatchCount++;
        }

        // Calculate percentage of criteria matched
        double matchPercentage = (criteriaMatchCount / 8.0) * 100; // 8 is the total number of criteria

        // If at least 70% of the criteria match, add the book to compatibleBooks
        if (matchPercentage >= 70) {
            compatibleBooks.insert(book.title);    // Insert each individual title into the set
        }
    }
    cout << compatibleBooks.size() << endl;
    return compatibleBooks;
}


// Updated takeQuiz function
void Book::takeQuiz() {
    auto newBooksInMemory = getBooksInMemory();
    cout << "Number of books in memory: " << newBooksInMemory.size() << endl;
    // Get user preferences
    auto priceRange = getPriceRange();
    auto preferredGenres = getGenrePreferences(getUniqueGenres());
    auto reviewRange = getReviewRange();
    bool kindleUnlimited = getBooleanPreference("Do you prefer Kindle Unlimited?");
    bool newEditorsPick = getBooleanPreference("Do you prefer Editor's Pick?");
    bool newBestSeller = getBooleanPreference("Do you prefer Best Seller?");
    bool goodReadsChoice = getBooleanPreference("Do you prefer Goodreads Choice?");

    // Get compatible books
    set<string> compBooks = getCompatibleBooks(newBooksInMemory, priceRange, preferredGenres, reviewRange, kindleUnlimited, newEditorsPick, newBestSeller, goodReadsChoice);


    // Display results
    if (!compBooks.empty()) {
        cout << "Compatible books based on your preferences:" << endl;
        int counter = 1;
        for (const auto& bookTitle : compBooks) {
            cout << counter << "). " << "TITLE: " << bookTitle << " | " << "RATINGS: " << stars << " | " << "PRICE: " << price <<endl;
            counter++;
            if (counter >= 21)
                break;
        }
    }
    else {
        cout << "No books found matching your preferences." << endl;
    }

}
void Book::search(){
    string ctgy, value;
    cout << "Which book attribute did you want to search?" << endl;
    cout << "(type title, author, best seller, editors choice, best seller, etc)" << endl;
    cin >> ctgy;
    cout << "Search the " << ctgy << " you are looking for\nPlease capitalize the first letter" << endl;
    cin.ignore();
    getline(cin, value);
    // for case insensitivity
    transform(ctgy.begin(), ctgy.end(), ctgy.begin(), ::tolower);
    // transform(value.begin(), value.end(), value.begin(), ::tolower);
    vector<Book> searchResults = searchBooks(ctgy, value);

    // Display search results
    if (!searchResults.empty()){
        cout << "\nSearch Results:\n" << endl;
        int counter = 1;
        for (const auto& book : searchResults) {
            cout << counter << "). " << "TITLE: " << book.getBooktitle() << " | " << "AUTHOR: " << book.getBookAuthor()
                 << " | " << "RATINGS: " << book.getRating() << " | " << "PRICE: " << book.getBookPrice()
                 << " | " << "GENRE: " << book.getBookGenre() <<endl;
            counter++;
            if (counter >= 16){
                break;
            }
        }
    }
    else{
        cout << "No books found under this search: " << value
             << "\nPlease try again" << endl;
    }

}
vector<Book> Book::searchBooks(const string &key, const string &search){
    vector<Book> books;

    for (auto [id, bk] : database){
        if (key == "title" && bk.getBooktitle().find(search) != string::npos || key == "author" && bk.getBookAuthor().find(search) != string::npos
            || key == "genre" && bk.getBookGenre().find(search) != string::npos || key == "best seller" && bk.getOneBestSeller() == true
            || key == "kindle unlimited" && bk.getOneKindleU() == true || key == "editors pick" && bk.getOneEditorsPick() == true
            || key == "good reads choice" && bk.getOneGoodReads()){
            books.push_back(bk);
        }
    }
    return books;
}
//Citation: Lecture Slides and Geeks for Geeks
void Book::heapify(vector<Book> &heap, int size, int i){
    int top = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // check left and right children to compare to top element
    if (left < size && heap[left].getRating() > heap[top].getRating()){
        top = left;
    }
    if (right < size && heap[right].getRating()> heap[top].getRating()){
        top = right;
    }
    if (top != i){
        swap(heap[i], heap[top]);
        heapify(heap, size, top);
    }
}
void Book::buildHeap(vector<Book> &heap){
    int size = heap.size();
    for (int i = size/2 - 1; i >=0; i--){
        heapify(heap, size, i);
    }
}
// sort by rating (highest to lowest if user requests for rate)
void Book::sortByRating(vector<Book> &books){
    // max heap
    int size = books.size();
    buildHeap(books);
    // extract element from heap one at a time
    for (int i = size - 1; i > 0; i--){
        swap(books[0], books[i]);
        heapify(books, i, 0);
    }

    reverse(books.begin(), books.end());
}

