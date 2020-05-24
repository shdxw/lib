
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
private:
    string name;
    string author;
public:
    Book(const string name, const string author) {
        this->name = name;
        this->author = author;
    }
    const string getName() const {
        return name;
    }
    const string getAuthor() const {
        return author;
    }

    friend ostream&operator << (ostream &out, const Book book) {//перегруз вывода
        return out << book.name << " - " << book.author << endl;
    }

    Book&operator = (const Book &book) { //перегруз присваивания
        name = book.name;
        author = book.author;
        return *this;
    }
};

class Library {
protected:
    vector<Book> Books;

public:
    Library(vector<Book> &books) {
        Books = books;
    }

    void add_book(Book &book) { //метод для добавления
        Books.push_back(book);
    }

    void del_book(vector<Book> Books,int i) { //метод для удаления
        Books.erase(Books.begin() + i);
    }

    int IsBookNamed(string name) { //поиск по названию
        size_t size = Books.size();

        for (int i = 0; i < size; i++) {
            if (name == Books[i].getName()) {
                return i;
            }
        }
        return -1;
    }

    int IsBook(const Book &book) { //поиск по названию и автору
        string name = book.getName();
        string author = book.getAuthor();
        size_t size = Books.size();

        for (int i = 0; i < size; i++) {
            if ((name == Books[i].getName()) && (author == Books[i].getAuthor())) {
                return i;
            }
        }
        return -1;
    }

    int IsBookAuthored(string author) { //поиск по автору
        size_t size = Books.size();

        for (int i = 0; i < size; i++) {
            if (author == Books[i].getAuthor()) {
                return i;
            }
        }
        return -1;
    }


};

class Worker : public Library {

public:
    Worker(vector<Book> Books) : Library(Books) {
        this->Books = Books;
    }

    Book Rent(string name, string author) {
        int i = IsBook({ name, author });
        Book book("","");
        if (i >= 0) {
            cout << "Получите свою книгу: " << Books[i] <<endl;
            book = Books[i];
            del_book(Books,i);
            return book;
        }
        else {
            cout << "Книги нет "<< endl;
            return book;
        }
    }
    Book RentNaz(string name) {
        int i = IsBookNamed(name);
        Book book("", "");
        if (i >= 0) {
            cout << "Получите свою книгу: "<< Books[i] << endl;
            book = Books[i];
            del_book(Books, i);
            return book;
        }
        else {
            cout << "Книги нет "<<endl;
            return book;
        }
    }
    Book RentAvtor(string author) {
        int i = IsBookAuthored(author);
        Book book("", "");
        if (i >= 0) {
            cout << "Получите свою книгу: "<< Books[i] << endl;
            book = Books[i];
            del_book(Books, i);
            return book;
        }
        else {
            cout << "Книги нет " << endl;
            return book;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Book A{ "Transformers", "Papa Joe" };
    Book B{ "Coming out", "Blue Jack" };
    Book C{ "NLO", "Ilon Musk" };
    Book D{ "Ya ustal", "Vlad B" };
    Book E{ "how to kill yslf", "Klevch Yurii" };
    Book F{ "Beskonechnoe leto", "Anon Group" };


    vector<Book> Books = {A,B,C,D,E,F};
    Library library(Books);

    Worker Worker(Books);
    Worker.Rent("how to kill yslf", "Klevch Yurii");

    Worker.RentAvtor("Ya hz che za avtor");

    Worker.RentNaz("Ya ustal");

    return 0;
}
