/*
 * VE280 Lab 7, SU2021
 * Created by cyx on 20-5-22.
 * Modified by makersmelx on June 28th, 2021.
 */

#ifndef COURSE_H
#define COURSE_H

/*
 * Task is used to represent tasks in a course.
 * type could be "Lab", "Project" and etc., which specifies the type of the task,
 * index is the number of task of this type,
 * dueMonth and dueDay specifies its due date
 */
struct Task {
    std::string type;
    int index{}; // Task index of type
    int dueMonth{};
    int dueDay{};
};

const int MAX_TASKS = 4; // default value of the maximum number of tasks in a course at a time

// an exception class
class TooManyTasks : public std::exception {
};

class Course {
public:
    // TODO: declare the methods and the destructor here
    virtual void updateTask(const std::string &type, int index, int dueMonth, int dueDay) = 0;
    virtual void finishTask(const std::string &type, int index, int finishMonth, int finishDay) = 0;
    virtual void print() = 0;
    //how to declare this destructor
    virtual ~Course(){};
};

Course *create(const std::string &classType, const std::string &courseCode, const int &size);

Course *create(const std::string &classType, const std::string &courseCode);

/*
 * EFFECTS: returns a pointer according to classType
 *          If classType is not "Technical" or "Upper Level Technical", returns a null pointer.
 *          If we have a third argument and it is an integer, the maximum number of tasks will be this integer
 *          otherwise, the maximum number of tasks is the default value.
 */

class TechnicalCourse : public Course {
protected:
    Task *tasks;
    int sizeTasks;
    int numTasks;
    std::string courseCode;
public:
    // TODO: implement the constructor
    TechnicalCourse(std::string courseCode, int size = MAX_TASKS):
        tasks(new Task[size]), sizeTasks(size), numTasks(0),courseCode(courseCode){
    }

    // TODO: declare and implement the destructor
    ~TechnicalCourse(){
        delete [] tasks;
    };

    // TODO: declare updateTask method
    void updateTask(const std::string &type, int index, int dueMonth, int dueDay);

    void finishTask(const std::string &type, int index, int finishMonth, int finishDay);

    void print();
};

class UpperLevelTechnicalCourse : public TechnicalCourse {
public:
    // TODO: implement the constructor
    UpperLevelTechnicalCourse(const std::string &courseCode, int size = MAX_TASKS):
        TechnicalCourse(courseCode, size){
    };

    // TODO: declare and implement the destructor
    ~UpperLevelTechnicalCourse(){
    };

    void updateTask(const std::string &type, int index, int dueMonth, int dueDay);
};

#endif //COURSE_H