#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

// Function prototypes
void examinerMenu();
void examineeMenu();
void makeExamination(const string &username);
void viewResultByUsername();
void viewAllResults();
void deleteStudent();
bool validateUsername(const string &username);
void registerExaminee();
void takeTest(const string &username);
void seeAnswerOfPreviousExams();
void seeRank();
void changePassword();

// Data structures
struct Question {
    string question;
    vector<string> options;
    char correctAnswer;
};

struct Exam {
    struct Question {
        string question;
        vector<string> options;
        char correctAnswer;
    };

    vector<Question> questions;
    vector<char> studentAnswers;
    string testType;
};


struct Student {
    string username;
    string name;
    string password;
    Exam exam;
};

map<string, Student> students;

// Main function
int main() {
    // Create a default student
    Student defaultStudent;
    defaultStudent.username = "default";
    students[defaultStudent.username] = defaultStudent;

    while (true) {
        cout << "Choose user type:\n";
        cout << "1. Examiner\n";
        cout << "2. Examinee\n";
        cout << "3. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                examinerMenu();
                break;
            case 2:
                examineeMenu();
                break;
            case 3:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

// Function definitions
void examinerMenu() {
    while (true) {
        cout << "\nExaminer Menu:\n";
        cout << "1. Make Examination\n";
        cout << "2. View Result by Username\n";
        cout << "3. View All Results\n";
        cout << "4. Delete Student\n";
        cout << "5. Back to Main Menu\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    string username;
                    cout << "Enter the username of the student to make an examination: ";
                    cin >> username;
                    makeExamination(username);
                }
                break;
            case 2:
                viewResultByUsername();
                break;
            case 3:
                viewAllResults();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void examineeMenu() {
    while (true) {
        cout << "\nExaminee Menu:\n";
        cout << "1. Register\n";
        cout << "2. Take Test\n";
        cout << "3. See Answer of Previous Exams\n";
        cout << "4. See Rank\n";
        cout << "5. Change Password\n";
        cout << "6. Back to Main Menu\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                registerExaminee();
                break;
            case 2:
                {
                    string username;
                    cout << "Enter your username to take the test: ";
                    cin >> username;
                    takeTest(username);
                }
                break;
            case 3:
                seeAnswerOfPreviousExams();
                break;
            case 4:
                seeRank();
                break;
            case 5:
                changePassword();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void makeExamination(const string &username) {
    if (validateUsername(username) && students.find(username) != students.end()) {
        Exam newExam;
        Exam::Question newQuestion;

        cout << "Enter the number of questions for the examination: ";
        int numQuestions;
        cin >> numQuestions;

        for (int i = 0; i < numQuestions; ++i) {
            cout << "Enter question " << i + 1 << ":\n";
            cout << "Question: ";
            cin.ignore();
            getline(cin, newQuestion.question);

            cout << "Enter the options (separated by spaces):\n";
            string option;
            for (char c = 'A'; c < 'A' + 4; ++c) {
                cout << c << ": ";
                cin >> option;
                newQuestion.options.push_back(option);
            }

            cout << "Enter the correct answer (A, B, C, or D): ";
            cin >> newQuestion.correctAnswer;

            newExam.questions.push_back(newQuestion);
            newQuestion.options.clear();  // Clear options for the next question
        }

        // Store the new exam
        students[username].exam = newExam;

        cout << "Examination created successfully for student " << username << ".\n";
    } else {
        cout << "Invalid username or Student with username " << username << " not found.\n";
    }
}

void viewResultByUsername() {
    string username;
    cout << "Enter the username of the student: ";
    cin >> username;

    if (validateUsername(username) && students.find(username) != students.end()) {
        Student &student = students[username];
        cout << "Result for Student " << username << ":\n";
        for (int i = 0; i < student.exam.questions.size(); ++i) {
            cout << "Question " << i + 1 << ": ";
            cout << "Correct Answer: " << student.exam.questions[i].correctAnswer << ", ";
            cout << "Student Answer: " << student.exam.studentAnswers[i] << "\n";
        }
    } else {
        cout << "Invalid username or Student with username " << username << " not found.\n";
    }
}

void viewAllResults() {
    cout << "All Results:\n";
    for (const auto &entry : students) {
        cout << "Username: " << entry.first << ", Name: " << entry.second.name << "\n";
        if (entry.second.exam.studentAnswers.empty()) {
            cout << "No exam results available.\n";
        } else {
            cout << "Exam Results:\n";
            for (int i = 0; i < entry.second.exam.questions.size(); ++i) {
                cout << "Question " << i + 1 << ": ";
                cout << "Correct Answer: " << entry.second.exam.questions[i].correctAnswer << ", ";
                cout << "Student Answer: " << entry.second.exam.studentAnswers[i] << "\n";
            }
        }
        cout << "\n";
    }
}

void deleteStudent() {
    string username;
    cout << "Enter the username of the student to delete: ";
    cin >> username;

    if (validateUsername(username) && students.find(username) != students.end()) {
        students.erase(username);
        cout << "Student with username " << username << " deleted successfully.\n";
    } else {
        cout << "Invalid username or Student with username " << username << " not found.\n";
    }
}

bool validateUsername(const string &username) {
    return !username.empty();
}

void registerExaminee() {
    string newUsername;
    cout << "Enter a new username for registration: ";
    cin >> newUsername;

    if (validateUsername(newUsername) && students.find(newUsername) == students.end()) {
        Student newExaminee;
        newExaminee.username = newUsername;

        cout << "Enter name for the new examinee: ";
        cin.ignore();
        getline(cin, newExaminee.name);

        cout << "Enter password for the new examinee: ";
        cin >> newExaminee.password;

        // Register the new examinee
        students[newUsername] = newExaminee;

        cout << "Examinee with username " << newUsername << " registered successfully.\n";
    } else {
        cout << "Invalid username or username already exists. Please choose a different username.\n";
    }
}

void takeTest(const string &username) {
    if (validateUsername(username) && students.find(username) != students.end()) {
        
        Student &student = students[username];
        if (student.exam.questions.empty()) {
            cout << "No questions available for the test.\n";
        } else {
            cout << "Taking the test for student " << username << ".\n";
           
            for (int i = 0; i < student.exam.questions.size(); ++i) {
                cout << "Question " << i + 1 << ": " << student.exam.questions[i].question << "\n";

                // Loop to present options for each question
                for (int j = 0; j < student.exam.questions[i].options.size(); ++j) {
                    cout << static_cast<char>('A' + j) << ": " << student.exam.questions[i].options[j] << "\n";
                }

                char answer;
                cout << "Enter your answer (A, B, C, or D): ";
                // Loop until a valid answer is provided
                while (true) {
                    cin >> answer;
                    if (answer >= 'A' && answer <= 'D') {
                        break;
                    } else {
                        cout << "Invalid answer. Please enter A, B, C, or D.\n";
                    }
                }

                student.exam.studentAnswers.push_back(answer);
            }
            cout << "Test completed for student " << username << ".\n";
        }
    } else {
        cout << "Invalid username or Student with username " << username << " not found.\n";
    }
}



void seeAnswerOfPreviousExams() {
    string username;
    cout << "Enter the username of the student to see answers of previous exams: ";
    cin >> username;

    if (validateUsername(username) && students.find(username) != students.end()) {
        Student &student = students[username];
      
        if (student.exam.studentAnswers.empty()) {
            cout << "No previous exam answers found for student " << username << ".\n";
        } else {
            cout << "Answers of previous exams for student " << username << ":\n";
            for (int i = 0; i<student.exam.questions.size(); ++i) {
                cout << "Question " << i + 1 << ": ";
                cout << "Correct Answer: " << student.exam.questions[i].correctAnswer << ", ";
                cout << "Student Answer: " << student.exam.studentAnswers[i] << "\n";
            }
        }
    } else {
        cout << "Invalid username or Student with username " << username << " not found.\n";
    }
}

void seeRank() {
    vector<pair<string, int>> ranks;

    for (const auto &entry : students) {
        const Student &student = entry.second;
        int correctAnswers = 0;

        // Count correct answers
        for (int i = 0; i < student.exam.questions.size(); ++i) {
            if (student.exam.studentAnswers[i] == student.exam.questions[i].correctAnswer) {
                correctAnswers++;
            }
        }

        ranks.emplace_back(student.username, correctAnswers);
    }

    // Sort ranks based on correct answers in descending order
    sort(ranks.begin(), ranks.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    // Display ranks
    cout << "Rankings:\n";
    for (int i = 0; i < ranks.size(); ++i) {
        cout << i + 1 << ". Username: " << ranks[i].first << ", Correct Answers: " << ranks[i].second << "\n";
    }
}

void changePassword() {
    string username;
    cout << "Enter the username of the student to change password: ";
    cin >> username;

    if (validateUsername(username) && students.find(username) != students.end()) {
        cout << "Enter the new password for student " << username << ": ";
        cin >> students[username].password;
        cout << "Password changed successfully for student " << username << ".\n";
    } else {
        cout << "Invalid username or Student with username " << username << " not found.\n";
    }
}
