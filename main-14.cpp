#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Source {
    string title;
    string type;
    int year;
    virtual void print() const = 0;
    virtual ~Source() {}
};

struct Book : public Source {
    string author;
    string category;

    Book(string t, string a, string c, int y) {
        title = t;
        author = a;
        category = c;
        year = y;
        type = "Книга";
    }

    void print() const override {
        cout << "Книга: " << title << ", Автор: " << author << ", Категорія: " << category << ", Рік: " << year << endl;
    }
};

struct Magazine : public Source {
    Magazine(string t, int y) {
        title = t;
        year = y;
        type = "Журнал";
    }

    void print() const override {
        cout << "Журнал: " << title << ", Рік: " << year << endl;
    }
};

struct Newspaper : public Source {
    Newspaper(string t, int y) {
        title = t;
        year = y;
        type = "Газета";
    }

    void print() const override {
        cout << "Газета: " << title << ", Рік: " << year << endl;
    }
};

vector<Source*> library;

void addSource(Source* source) {
    library.push_back(source);
}

void viewAllSources() {
    for (const auto& source : library) {
        source->print();
    }
}

void removeSource(string title) {
    library.erase(
        remove_if(library.begin(), library.end(),
            [&](Source* source) { return source->title == title; }),
        library.end()
    );
}

void sortByTypeAndTitle() {
    sort(library.begin(), library.end(),
        [](Source* a, Source* b) {
            return a->type == b->type ? a->title < b->title : a->type < b->type;
        });
}

Source* findBook(string author, string title) {
    for (const auto& source : library) {
        if (source->type == "Книга") {
            Book* book = static_cast<Book*>(source);
            if (book->author == author && book->title == title) {
                return source;
            }
        }
    }
    return nullptr;
}

int countBooksByCategory(string category) {
    int count = 0;
    for (const auto& source : library) {
        if (source->type == "Книга") {
            Book* book = static_cast<Book*>(source);
            if (book->category == category) {
                count++;
            }
        }
    }
    return count;
}

void removeNewspapersByYear(int year) {
    library.erase(
        remove_if(library.begin(), library.end(),
            [&](Source* source) { return source->type == "Газета" && source->year == year; }),
        library.end()
    );
}

void displayMenu() {
    cout << "Меню:\n";
    cout << "1. Заповнення бази даних\n";
    cout << "2. Перегляд даних про всі джерела\n";
    cout << "3. Доповнення бази даних записом джерела\n";
    cout << "4. Видалення джерела із бази даних\n";
    cout << "5. Упорядкування по полях\n";
    cout << "6. Пошук книги\n";
    cout << "7. Вибірка книг за категорією або автором\n";
    cout << "8. Обчислення кількості книг певної категорії\n";
    cout << "9. Видалення газет за певний рік\n";
    cout << "0. Вихід\n";
}

void addSourceInteractive() {
    int choice;
    cout << "Оберіть тип джерела (1 - Книга, 2 - Журнал, 3 - Газета): ";
    cin >> choice;
    cin.ignore();
    
    string title;
    int year;
    
    if (choice == 1) {
        string author, category;
        cout << "Введіть назву книги: ";
        getline(cin, title);
        cout << "Введіть автора книги: ";
        getline(cin, author);
        cout << "Введіть категорію книги: ";
        getline(cin, category);
        cout << "Введіть рік видання: ";
        cin >> year;
        addSource(new Book(title, author, category, year));
    }
    else if (choice == 2) {
        cout << "Введіть назву журналу: ";
        getline(cin, title);
        cout << "Введіть рік видання: ";
        cin >> year;
        addSource(new Magazine(title, year));
    }
    else if (choice == 3) {
        cout << "Введіть назву газети: ";
        getline(cin, title);
        cout << "Введіть рік видання: ";
        cin >> year;
        addSource(new Newspaper(title, year));
    }
    else {
        cout << "Невірний вибір.\n";
    }
}

int main() {
    int choice;
    
    do {
        displayMenu();
        cout << "Оберіть опцію: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                addSourceInteractive();
                break;
            case 2:
                viewAllSources();
                break;
            case 3:
                addSourceInteractive();
                break;
            case 4: {
                string title;
                cout << "Введіть назву джерела для видалення: ";
                getline(cin, title);
                removeSource(title);
                break;
            }
            case 5:
                sortByTypeAndTitle();
                cout << "Джерела упорядковано.\n";
                break;
            case 6: {
                string author, title;
                cout << "Введіть автора книги: ";
                getline(cin, author);
                cout << "Введіть назву книги: ";
                getline(cin, title);
                Source* foundBook = findBook(author, title);
                if (foundBook) {
                    foundBook->print();
                } else {
                    cout << "Книга не знайдена.\n";
                }
                break;
            }
            case 7: {
                int subChoice;
                cout << "1. Вибірка книг за категорією\n2. Вибірка книг за автором\n";
                cin >> subChoice;
                cin.ignore();
                
                if (subChoice == 1) {
                    string category;
                    cout << "Введіть категорію: ";
                    getline(cin, category);
                    int count = countBooksByCategory(category);
                    cout << "Кількість книг категорії '" << category << "': " << count << endl;
                } else if (subChoice == 2) {
                    string author;
                    cout << "Введіть автора: ";
                    getline(cin, author);
                    for (const auto& source : library) {
                        if (source->type == "Книга") {
                            Book* book = static_cast<Book*>(source);
                            if (book->author == author) {
                                book->print();
                            }
                        }
                    }
                }
                break;
            }
            case 8: {
                string category;
                cout << "Введіть категорію для підрахунку: ";
                getline(cin, category);
                int count = countBooksByCategory(category);
                cout << "Кількість книг у категорії '" << category << "': " << count << endl;
                break;
            }
            case 9: {
                int year;
                cout << "Введіть рік для видалення газет: ";
                cin >> year;
                removeNewspapersByYear(year);
                break;
            }
            case 0:
                cout << "Вихід.\n";
                break;
            default:
                cout << "Невірний вибір.\n";
        }
        
    } while (choice != 0);
    
    for (auto source : library) {
        delete source;
    }
    
    return 0;
}
