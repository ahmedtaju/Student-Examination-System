# Exam Management System - README

## Overview
This **Exam Management System** is a simple C++ console application designed to manage examinations for examinees under the supervision of an examiner. The application includes functionalities like creating examinations, taking tests, viewing results, managing students, and more.

---

## Features
1. **User Types**:
   - **Examiner**:
     - Create examinations.
     - View results (individual and all).
     - Delete student data.
   - **Examinee**:
     - Register as a student.
     - Take tests.
     - View answers of previous exams.
     - View rankings.
     - Change password.

2. **Core Functionalities**:
   - Examination creation with multiple-choice questions.
   - Automatic storage and validation of results.
   - Ranking students based on test performance.

3. **Data Management**:
   - `map<string, Student>` is used to manage student data efficiently.
   - Each student has their own examination history and credentials.

---

## Data Structures
- **`struct Question`**: Represents a single question with multiple-choice options.
- **`struct Exam`**: Contains questions, student answers, and test metadata.
- **`struct Student`**: Holds user credentials, exam details, and other information.

---

## How to Run
1. Compile the program using any C++ compiler:
   ```bash
   g++ -o exam_system exam_system.cpp
   ```
2. Run the executable:
   ```bash
   ./exam_system
   ```

---

## User Guide
1. **Examiner Actions**:
   - Login as an **Examiner** and create exams, view results, or manage students.
   - Follow the menu prompts to perform desired actions.

2. **Examinee Actions**:
   - Register with a unique username and password.
   - Take tests, view previous answers, or change your password.

3. **Ranking**:
   - Rankings are calculated based on the number of correct answers in the exam.

---

## File Structure
- **`main` function**: Serves as the entry point for the application.
- **Examiner Menu**: Handles exam management functions.
- **Examinee Menu**: Handles test-taking and other student functions.
- **Helper Functions**:
  - `validateUsername`, `makeExamination`, `takeTest`, `seeRank`, etc.

---

## Future Improvements
- Add file storage for persistent data management.
- Enhance security for password storage.
- Improve input validation and error handling.
- Add more detailed analytics for results.

---

## Contributing
Feel free to fork this project and make contributions. Submit pull requests for improvements or new features.

---

**Enjoy the Exam Management System!**
