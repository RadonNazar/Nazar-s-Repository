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

int main() {
    addSource(new Book("Майстер і Маргарита", "Булгаков", "Фантастика", 1967));
    addSource(new Book("Злочин і кара", "Достоєвський", "Класика", 1866));
    addSource(new Magazine("National Geographic", 2020));
    addSource(new Newspaper("The New York Times", 2021));
    
    cout << "Всі джерела:" << endl;
    viewAllSources();
    
    Source* foundBook = findBook("Булгаков", "Майстер і Маргарита");
    if (foundBook) {
        cout << "\nЗнайдена книга:" << endl;
        foundBook->print();
    }

    int count = countBooksByCategory("Фантастика");
    cout << "\nКількість книг категорії 'Фантастика': " << count << endl;

    removeNewspapersByYear(2021);
    cout << "\nБаза даних після видалення газет за 2021 рік:" << endl;
    viewAllSources();

    for (auto source : library) {
        delete source;
    }

    return 0;
}