Hey guys! This page will explain our project but for rn we can use this to plan it out here
i'm using vs code instead of clion so we can live code with each other instead of uploading to git each time we make changes
here is a rough plan of our project
--> site description can replace this later
------------------------------------------------------------

1. Project Setup
Backend: Use C++ for core data processing, algorithms, and integration with the frontend.
Frontend: Use SFML for a desktop application or HTML/CSS/JavaScript/React for a web-based solution.
Dataset Integration: Utilize Kaggle's API to fetch <kindle_data-vs.csv> and preprocess the data.

2. Core Components
A. Data Storage Structure
    Implement a Binary Search Tree (BST) or AVL Tree for efficient data storage.
    Each node will store:
    Title, ID, Author, Genre, Date, Number of Copies, Rating.
    Alternatively, use a HashMap for faster lookups (by title or ID).

B. Sorting Mechanism
    Use:
    QuickSort or MergeSort for efficient multi-criteria sorting.
    STL std::sort with custom comparators for flexibility in sorting attributes (e.g., title, genre).

C. Max Heap / Priority Queue
    Build a Max Heap for sorting by:
    Rating (highest-rated books).
    Availability (most available copies).
    Use STL std::priority_queue for quick implementation.

D. Comparison Tool
    Implement:
    Keyword Matching: Tokenize book descriptions and find similar books based on overlapping keywords.
    Cosine Similarity or TF-IDF: Advanced semantic analysis for plot similarity.

E. Cart for Borrowing/Reading
    Use a simple Queue or Vector to represent the cart.
    Allow operations:
    Add/Remove Books.
    View Cart Contents.

3. Frontend-Backend Integration
    A. SFML (Desktop GUI)
        Use SFML for:
        Book search/sort forms.
        Displaying lists.
        Cart management.
        Communicate via files or sockets with the C++ backend for large operations.
    B. Web (HTML/CSS/React)
        Use React for dynamic UI.
        Setup a REST API in C++ using:
        Drogon or Crow frameworks.
        Fetch data using Axios or Fetch API in React.
4. Implementation Steps
    A. Backend Development
        Dataset Loader: Create a parser to read <kindle_data-vs.csv> into your data structure.
        Sorting Algorithms: Implement flexible sorting functions.
        Heap/Priority Queue: Build a heap structure for specialized sorting.
        Comparison Tool: Write a module for semantic analysis or keyword matching.
    B. Frontend Development
        UI/UX Design:
        SFML: Create interactive windows.
        React: Build dynamic forms, tables, and cart UI.
        API Integration:
        Set up endpoints for search, sorting, and cart operations.
    C. Testing & Debugging
        Use test data to validate:
        Sorting accuracy.
        Heap operations.
        Comparison results.
5. Required Tools
    Backend:
    C++ Compiler (e.g., GCC, MSVC).
    Kaggle API for dataset handling.
    Frontend:
    SFML (for desktop).
    Node.js (for React development).
    Integration:
    REST API frameworks (Drogon/Crow).
6. Deployment
    Desktop: Package as a standalone executable.
    Web: Deploy on a local server (e.g., Nginx) or cloud platforms like Heroku.