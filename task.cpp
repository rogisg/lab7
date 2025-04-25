#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Задание 1
void saveToFile(const string& filename, const vector<string>& data) {
    ofstream file(filename);
    for (const auto& word : data) {
        file << word << endl;
    }
}

void loadFromFile(const string& filename, vector<string>& outData) {
    ifstream file(filename);
    string word;
    while (getline(file, word)) {
        outData.push_back(word);
    }
}

// Задание 2
struct Book {
    string Author;
    string Title;
    int Year;
};

void saveToFile(const string& filename, const vector<Book>& data) {
    ofstream file(filename);
    for (const auto& book : data) {
        file << book.Author << endl;
        file << book.Title << endl;
        file << book.Year << endl;
    }
}

void loadFromFile(const string& filename, vector<Book>& outData) {
    ifstream file(filename);
    Book book;
    while (getline(file, book.Author) && 
           getline(file, book.Title) && 
           (file >> book.Year)) {
        outData.push_back(book);
        file.ignore();
    }
}

// Задание 3
enum Score {
    Unsatisfactorily = 2,
    Satisfactorily,
    Good,
    Excellent
};

struct Student {
    string Name;
    int Year;
    map<string, Score> RecordBook;
};

using Groups = map<string, vector<Student>>;

void saveToFile(const string& filename, const Groups& groups) {
    ofstream file(filename);
    for (const auto& group : groups) {
        file << group.first << endl;
        file << group.second.size() << endl;
        for (const auto& student : group.second) {
            file << student.Name << endl;
            file << student.Year << endl;
            file << student.RecordBook.size() << endl;
            for (const auto& record : student.RecordBook) {
                file << record.first << endl;
                file << record.second << endl;
            }
        }
    }
}

void loadFromFile(const string& filename, Groups& outGroups) {
    ifstream file(filename);
    string groupName;
    while (getline(file, groupName)) {
        int studentCount;
        file >> studentCount;
        file.ignore();
        
        vector<Student> students;
        for (int i = 0; i < studentCount; i++) {
            Student student;
            getline(file, student.Name);
            file >> student.Year;
            file.ignore();
            
            int recordCount;
            file >> recordCount;
            file.ignore();
            
            for (int j = 0; j < recordCount; j++) {
                string subject;
                int score;
                getline(file, subject);
                file >> score;
                file.ignore();
                student.RecordBook[subject] = static_cast<Score>(score);
            }
            students.push_back(student);
        }
        outGroups[groupName] = students;
    }
}

int main() {
    vector<string> words = {"word1", "word2", "word3"};
    saveToFile("words.txt", words);
    
    vector<Book> books = {{"Author1", "Title1", 2000}, {"Author2", "Title2", 2005}};
    saveToFile("books.txt", books);
    
    Groups groups;
    Student s1 = {"Ivan", 2020, {{"Math", Excellent}, {"Physics", Good}}};
    Student s2 = {"Maria", 2021, {{"Math", Good}, {"Chemistry", Satisfactorily}}};
    groups["Group1"] = {s1, s2};
    saveToFile("groups.txt", groups);
    
    return 0;
}
