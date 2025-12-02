#include <string>
#include <iostream>
#include"Member.h"
#include"Book.h"
using namespace std;

class Loan{
private:
    string isbn;
    string memberId;
    string startDate;
    string dueDate;
    bool returned;

public:
    Loan(const string& isbn, const string& memberId, const string& startDate, const string& dueDate, bool returned = false)
        : isbn(isbn), memberId(memberId), startDate(startDate), dueDate(dueDate), returned(returned)
    {
        if (this->dueDate < this->startDate) {
            cerr << "Invalid dates: dueDate < startDate. Adjusting dueDate to startDate." << endl;
            this->dueDate = this->startDate;
        }
    }

    void markReturned() {
        returned = true;
    }

    bool isOverdue(const string& today) const {
        if (returned) return false;
        return dueDate < today;
    }

    string to_string() const {
        return "Loan: ISBN: " + isbn + ", Member: " + memberId + 
               ", Start: " + startDate + ", Due: " + dueDate + 
               ", Returned: " + (returned ? "Yes" : "No");
    }
};