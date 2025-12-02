#include <iostream>
#include "Library.h"


using namespace std;

int main() {
    Library lib;

    Author a1{"Ivan Vazov", 1850};
    Author a2{"Hristo Botev", 1848};

    Book book1{"Pod igoto", a1, 1894, 25.50, "ISBN-001"};
    Book book2{"Nema zemya", a1, 1900, 18.90, "ISBN-002"};
    Book book3{"Hadji Dimitar", a2, 1863, 15.00, "ISBN-003"};

    lib.addAuthor(a1);
    lib.addAuthor(a2);

    lib.addBook(book1);
    lib.addBook(book2);
    lib.addBook(book3);

    Member m1{"Petar Petrov", "M001", 2023};
    Member m2{"Maria Ivanova", "M002", 2020};
    lib.addMember(m1);
    lib.addMember(m2);

    cout << "=== Initial library snapshot ===\n";
    cout << lib.to_string() << "\n";

    cout << "Total books (static): " << Book::getTotalBooks() << "\n\n";

    cout << "=== Loan object tests ===\n";
    Loan loan1("ISBN-001", "M001", "2025-11-03", "2025-11-17");
    cout << loan1.to_string() << "\n";
    cout << "Is loan1 overdue on 2025-11-18? " << boolalpha << loan1.isOverdue("2025-11-18") << "\n";
    loan1.markReturned();
    cout << "After marking returned: " << loan1.to_string() << "\n\n";

    cout << "=== Library loan flow ===\n";
    lib.loanBook("ISBN-001", "M001", "2025-11-03", "2025-11-17");
    lib.isBookAvailable("ISBN-001");

    lib.loanBook("NO-ISBN", "M001", "2025-11-03", "2025-11-17");

    lib.returnBook("ISBN-001", "M001");
    lib.isBookAvailable("ISBN-001");

    cout << "\nBooks by 'Vazov':\n";
    for (const auto& bk : lib.findBooksByAuthor("Vazov")) {
        cout << " - " << bk.to_string() << "\n";
    }

    cout << "\n=== End of tests ===\n";
    return 0;
}