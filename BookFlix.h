#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>
#include <iomanip>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include <bits/stdc++.h>
#include <utility>
using namespace std;

class Book {
private:
    set<string> uniqueGenres;
    vector<string> similarBooks;
    vector<string> titleSet;
    vector<double> starsNum;
    vector<double> priceNum;
    vector<bool> isUnlimited;
    vector<bool> editorsPick;
    vector<bool> goodReads;
    vector<bool> bestSeller;
    vector<int> reviewNum;



    const vector<string>& books;

    string asin;
    string title;
    string author;
    string soldBy;
    string imgUrl;
    string productURL;
    string stars;
    string reviews;
    string price;
    bool isKindleUnlimited{};
    string category_id;
    bool isBestSeller{};
    bool isEditorsPick{};
    bool isGoodReadsChoice{};
    string publishedDate;
    string category_name;
    string filename;

    vector<Book> booksInMemory;
    string formatBookDetails() const;

public:
    Book(string asin, string title, string author, string soldBy, string imgUrl, string productURL, string stars,
         string reviews, string price, bool isKindleUnlimited, string category_id, bool isBestSeller,
         bool isEditorsPick, bool isGoodReadsChoice, string publishedDate, string category_name,
         const vector<string> &books)
    : asin(asin), title(title), author(author), soldBy(soldBy), imgUrl(imgUrl), productURL(productURL), stars(stars), reviews(reviews),
      price(price), isKindleUnlimited(isKindleUnlimited), category_id(category_id), isBestSeller(isBestSeller), isEditorsPick(isEditorsPick),
      isGoodReadsChoice(isGoodReadsChoice), publishedDate(publishedDate), category_name(category_name), books(books) {}
    Book(const string& filename, const vector<string>& books);
    unordered_map<string, Book> database;

    void preprocessFile();
    void welcomeScreen();
    void search();
    vector<double> getPriceNum() const;
    vector<double> getStarsNum() const;
    set<string> getUniqueGenres() const;
    vector<string> getTitle() const;
    vector<bool> getIsUnlimited() const;
    vector<bool> getEditorsPick() const;
    vector<bool> getGoodReads() const;
    vector<bool> getBestSeller() const;
    vector<int> getReviewNum() const;

    void takeQuiz();

    vector<Book> getBooksInMemory();

    set<string> getCompatibleBooks(
            vector<Book>& booksInMemoryParam,
            pair<double, double>& priceRangeParam,
            const set<string>& preferredGenresParam,
            const pair<int, int>& reviewRangeParam,
            bool kindleUnlimitedParam,
            bool editorsPickParam,
            bool bestSellerParam,
            bool goodReadsChoiceParam
    );

    // swap function to fix swap/reverse issue
    // Citation: https://www.geeksforgeeks.org/friend-class-function-cpp/
    friend void swap(Book& a, Book& b) noexcept {
        using std::swap;
        swap(a.asin, b.asin);
        swap(a.title, b.title);
        swap(a.author, b.author);
        swap(a.category_name, b.category_name);
        swap(a.price, b.price);
        swap(a.stars, b.stars);
        swap(a.isBestSeller, b.isBestSeller);
        swap(a.isEditorsPick, b.isEditorsPick);
        swap(a.isGoodReadsChoice, b.isGoodReadsChoice);
        swap(a.isKindleUnlimited, b.isKindleUnlimited);
    }
//    // getter functiosn to call member variables, one at a time
    string getBooktitle() const{
        return title;
    }
    string getBookAuthor() const{
        return author;
    }
    string getBookGenre() const{
        return category_name;
    }
    int getAsin() const{
        return stoi(asin);
    }
    bool getOneBestSeller() const{
        return isBestSeller;
    }
    bool getOneKindleU() const{
        return isKindleUnlimited;
    }
    bool getOneEditorsPick() const{
        return isEditorsPick;
    }
    bool getOneGoodReads() const{
        return isGoodReadsChoice;
    }
    double getRating() const{
        if (stars.empty() || !isdigit(stars[0])){
            return 0.0;
        }
        return stod(stars);
    }

    string getBookPrice() const{
        return price;
    }
    // store attributes into map
    void addBook(const Book &book){
        database.emplace(book.title, book);

    }
    void heap(){
        vector<Book> books;
        for (const auto &[id, bk] : database){
            books.push_back(bk);
        }
        sortByRating(books);
    }
    vector<Book> searchBooks(const string &key, const string &search);
    void heapify(vector<Book> &heap, int size, int i);
    void buildHeap(vector<Book> &heap);
    void sortByRating(vector<Book> &books);
};

