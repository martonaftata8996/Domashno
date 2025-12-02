#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include "Author.h"

class Book {
private:
    std::string title;
    Author author;
    int year;
    double price;
    std::string isbn;

    inline static int totalBooks = 0; 

public:
    Book()
        : title("Unknown"), author(), year(2000), price(0.0), isbn("000-000") {
        totalBooks++; 
    }

    Book(std::string t, Author a, int y, double p, std::string i)
        : title(std::move(t)), author(std::move(a)), isbn(std::move(i)) {
        
        setYear(y);
        setPrice(p);
        totalBooks++;
    }
    ~Book() {
        totalBooks--; 
    }

    Book(const Book& other)
        : title(other.title), author(other.author), year(other.year), 
          price(other.price), isbn(other.isbn) {
        totalBooks++;
    }

    Book(Book&& other) noexcept
        : title(std::move(other.title)), author(std::move(other.author)), 
          year(other.year), price(other.price), isbn(std::move(other.isbn)) {
        totalBooks++;
        
        other.year = 0;
        other.price = 0.0;
    }

    Book& operator=(const Book& other) {
        if (this != &other) {
            title = other.title;
            author = other.author;
            year = other.year;
            price = other.price;
            isbn = other.isbn;
        }
        return *this;
    }

    Book& operator=(Book&& other) noexcept {
        if (this != &other) {
            title = std::move(other.title);
            author = std::move(other.author);
            year = other.year;
            price = other.price;
            isbn = std::move(other.isbn);

            other.year = 0;
            other.price = 0.0;
        }
        return *this;
    }


    void setPrice(double p) {
        if (p >= 0) {
            price = p;
        } else {
            std::cerr << "Warning: Price cannot be negative. Defaulting to 0.\n";
            price = 0.0;
        }
    }

    void setYear(int y) {
        if (y > 0 && y <= 2025) { 
            year = y;
        } else {
            year = 2000;
        }
    }

    std::string to_string() const {
          std::stringstream ss;
          ss << "'" << title << "' by " << author.getName()
              << " (" << year << "), $" << price
              << " [ISBN: " << isbn << "]";
        return ss.str();
    }

    static int getTotalBooks() {
        return totalBooks;
    }
};

#endif // BOOK_H