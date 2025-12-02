#include <string>
#include <vector>
#include <iostream>
#include "Author.h"
#include "Book.h"
#include "Member.h"
#include "Loan.h"
using namespace std;

class Library{
private:
    vector<Book> books;
    vector<Author> authors;
    vector<Loan> loans;
    vector<Member> members;
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }
    void addAuthor(const Author& author) {
        authors.push_back(author);
    }
    void addMember(const Member& member) {
        members.push_back(member);
    }
    void addLoan(const Loan& loan) {
        loans.push_back(loan);
    }
    void hasBook(const string& isbn) const {
        for (const auto& book : books) {
            if (book.to_string().find(isbn) != string::npos) {
                cout << "Book found: " << book.to_string() << endl;
                return;
            }
        }
        cout << "Book with ISBN " << isbn << " not found." << endl;
    }
    void isBookAvailable(const string& isbn) const {
        for (const auto& loan : loans) {
            if (loan.to_string().find(isbn) != string::npos && !loan.isOverdue("2024-12-31")) {
                cout << "Book with ISBN " << isbn << " is currently on loan." << endl;
                return;
            }
        }
        cout << "Book with ISBN " << isbn << " is available." << endl;
    }
    void loanBook(const string& isbn, const string& memberId, const string& startDate, const string& dueDate) {
        for (const auto& book : books) {
            if (book.to_string().find(isbn) != string::npos) {
                loans.emplace_back(isbn, memberId, startDate, dueDate);
                cout << "Book with ISBN " << isbn << " loaned to member " << memberId << "." << endl;
                return;
            }
        }
        cout << "Book with ISBN " << isbn << " not found. Cannot loan." << endl;
    }

    void returnBook(const string& isbn, const string& memberId) {
        for (auto& loan : loans) {
            if (loan.to_string().find(isbn) != string::npos && loan.to_string().find(memberId) != string::npos) {
                loan.markReturned();
                cout << "Book with ISBN " << isbn << " returned by member " << memberId << "." << endl;
                return;
            }
        }
        cout << "No active loan found for book with ISBN " << isbn << " and member " << memberId << "." << endl;
    }

    vector<Book> findBooksByAuthor(const string& authorName) const {
        vector<Book> results;
        for (const auto& book : books) {
            if (book.to_string().find(authorName) != string::npos) {
                results.push_back(book);
            }
        }
        return results;
    }

    string to_string() const {
        string result = "Library contains:\n";
        result += "Books:\n";
        for (const auto& book : books) {
            result += book.to_string() + "\n";
        }
        result += "Authors:\n";
        for (const auto& author : authors) {
            result += author.to_string() + "\n";
        }
        result += "Members:\n";
        for (const auto& member : members) {
            result += member.to_string() + "\n";
        }
        result += "Loans:\n";
        for (const auto& loan : loans) {
            result += loan.to_string() + "\n";
        }
        return result;
    }
};