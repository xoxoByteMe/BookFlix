#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

// book information
class Books{
    string title;
    string author;
    int id;
    string genre;
    string date;
    int avail_copies;
    float rating;
    string description;
};

class Library{
    // quick id lookup using hashmap 
    unordered_map<int, Books> database;

    // group by author, genre, title, etc
    map<string, vector<Books>> authorMap;
    map<string, vector<Books>> genreMap;

    // parsing functions
    void loadCSV(string &path);

    //sorting and more...

};

