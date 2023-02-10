//
// Created by james on 2023/2/3.
//

#ifndef CPLUS_DEMO_STUDENT_H
#define CPLUS_DEMO_STUDENT_H


class Student {
public:
    int age;

    int height;

    int getAge();

    int getSalary();

    Student() {
        this->age = 0;
        this->height = 0;
        this->salary = 0;
    }

    Student(int age, int height, int salary) {
        this->age = age;
        this->height = height;
        this->salary = salary;
    }

private:
    int salary;
};


#endif //CPLUS_DEMO_STUDENT_H
