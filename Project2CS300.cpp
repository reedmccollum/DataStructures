//============================================================================
// Name        : Project2CS300.cpp
// Author      : Reed McCollum
// Version     : 1.0
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Global Variables

struct Course {
    string courseId;
    string courseTitle;
    vector<string> prereqs;
    Course() {
        courseId = "";
        courseTitle = "";
        prereqs = {};
    }


};

vector<Course*> courseList;



/**
* Load file into Course Vector
* 
* @param fileName Name of file being loaded into vector
*/


void loadFile(string fileName) {
    //structure handlers
    string courseLine, courseItem;
    vector<string> course;
    vector<vector<string>> allCourses;
    // Open file to read
    fstream fin(fileName, ios::in);
    // Runs while file is open
    if (fin.is_open()) {
        //While there is a next line in file
        while(getline(fin, courseLine)) {
            //Clear last entry of course
            course.clear();
            //Intake line of file into courseLine
            stringstream str(courseLine);
            //While str has items seperated by commas
            while (getline(str, courseItem, ',')) {
                //Insert items into vector course
                course.push_back(courseItem);
            }
            //Insert courses into allCourses
            allCourses.push_back(course);

        }

    }
    //Else file not found, return
    else {
        
        cout << "Could not find file. Please try different file name. Failed file name:  "
            << fileName << endl << endl;
        return;

    }


    

    // For each course in allCourses
    for (int i = 0; i < allCourses.size(); i++) {
        //Create newCourse which is a Course Struct
        Course* newCourse = new Course();
        //For each entry in each course
        for (int j = 0; j < allCourses[i].size(); j++) {
            //First course entry is courseId
            if (j == 0) {
                newCourse->courseId  = allCourses[i][j];
            }
            //Second course entry is courseTitle
            if (j == 1) {
                newCourse->courseTitle = allCourses[i][j];
            }
            //All other entries are prereqs
            if (j > 1) {
                newCourse->prereqs.push_back(allCourses[i][j]);
            }
        
        }
       //Add each newCourse to the global courseList
       courseList.push_back(newCourse);
    }

    cout << "File loaded successfully" << endl << endl;
}


/**
* Compare two course's courseId's and return the true if the first is smaller
* 
* @param a First course to compare
* @param b Second course to compare
* 
* @returns bool
*/
bool compareCourseId(Course* a, Course* b) {
    // Returns true if a's courseId is smaller, false otherwise
    return (a->courseId < b->courseId);
}

/**
*   Prints out list with given Course Vector
* 
* @param givenCourseList The Course Vector to be displayed
*
*/
void printCourseList(vector<Course*> givenCourseList) {
    // Declared string prior to loop
    string printedStr;
    // for each course in givenCourseList
    for (Course* currCourse : givenCourseList) {
        // Clear the printedStr
        printedStr.clear();
        // Add the courseId and courseTitle to the printedStr
        printedStr = currCourse->courseId + " | " + currCourse->courseTitle;
        // If the currCourse has entries in prereqs
        if (!currCourse->prereqs.empty()) {
            //Make a new String Vector from currCourse's prereqs
            vector<string> currPrereqs = currCourse->prereqs;
            // For each entry in currPrereqs
            for (string prereq : currPrereqs) {
                // Add each Prereq to the printedStr
                printedStr += " | " + prereq;
            }
            
        }
        
        // Print printedStr for each course
        cout << printedStr << endl;
    }
}

/**
*  Sorts and prints the courseList
*/
void sortedCourseList() {
    // Sort the courseList from beginning to end by comparing courseId's
    sort(courseList.begin(), courseList.end(), compareCourseId);
    // Print the courseList
    printCourseList(courseList);

}

/**
*
* Search for a course in courseList based on courseId
* 
* @param searchId The courseId being searched for
*/

void searchCourse(string searchId) {
    // Convert the given courseId to all capital letters
    string upperSearchId = searchId;
    transform(upperSearchId.begin(), upperSearchId.end(), upperSearchId.begin(), ::toupper);
    // for each Course in the courseList
    for (Course* currCourse : courseList) {
        // If the currCourse's courseId matches the uppercase searchId
        if (upperSearchId == currCourse->courseId) {
            // Create new string
            string printedStr;
            
            // Add course title to string 
            printedStr = currCourse->courseTitle;

            // If the course has prereqs, add them to the string
            if (!currCourse->prereqs.empty()) {
               vector<string> currPrereqs = currCourse->prereqs;
                for (string prereq : currPrereqs) {
                    printedStr += " | " + prereq;
                }

            }
            // Print the string and return
            cout << printedStr << endl;
            return;

        }

    }
    // If searchId not found in courseList, return
    cout << "Course with course ID: " << searchId << " not found." << endl;
}

int main()
{
    // Variable declarations
    int menuChoice = 0;
    string fileGiven;
    string courseIdGiven;

    // While menuChoice is not exit num (9)
    while (menuChoice!=9) {
        // Print out menu of choices
        cout << endl;
        cout << "Welcome to the Course Planner:" << endl << endl;
        cout << "  1. Load File" << endl;
        cout << "  2. Display Courses" << endl;
        cout << "  3. Find course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Please select an option from the menu: ";
        // Intake new selection
        cin >> menuChoice;
        switch (menuChoice) {
        case 1:
            // Intake string for file name, use to call loadFile
            fileGiven.clear();
            cout << "Please input the name of the file you would like to load from." << endl
                << "Include the file extension .csv in the name: ";
            cin >> fileGiven;
            loadFile(fileGiven);
            break;
        case 2:
            // Print sorted courseList
            sortedCourseList();
            break;
        case 3:
            // Intake courseId, use to call searchCourse
            courseIdGiven.clear();
            cout << "Please input the CourseID you would like to receive information about: " ;
            cin >> courseIdGiven;
            searchCourse(courseIdGiven);
            break;
        case 9:
            break;
        }
    }
    // End program
    cout << "Good bye" << endl;
    return 0;
}

