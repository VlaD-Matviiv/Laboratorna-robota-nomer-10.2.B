// Lab 10.2.B

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <Windows.h>

using namespace std;

struct Student 
{
    string lastName;   
    int course;        
    enum Specialty { ComputerScience, Informatics, MathAndEconomics, PhysicsAndInformatics, LaborTraining } specialty;
    union Marks 
    {
        struct 
        {
            int physics;
            int math;
            int programming;
        } compSci;
        struct 
        {
            int physics;
            int math;
            int numerics;
        } informatics;
        struct 
        {
            int physics;
            int math;
            int pedagogy;
        } otherSpecialty;
    } marks;
};

void inputStudent(Student& s) 
{
    cout << "������� ��������: ";
    cin >> s.lastName;
    cout << "����: ";
    cin >> s.course;

    cout << "������������ (1 - ����'����� �����, 2 - �����������, 3 - ���������� �� ��������, 4 - Գ���� �� �����������, 5 - ������� ��������): ";
    int spec;
    cin >> spec;
    s.specialty = static_cast<Student::Specialty>(spec - 1);

    cout << "������ � ������: ";
    cin >> s.marks.compSci.physics; 
    cout << "������ � ����������: ";
    cin >> s.marks.compSci.math;

    if (s.specialty == Student::ComputerScience) 
    {
        cout << "������ � �������������: ";
        cin >> s.marks.compSci.programming;
    }
    else if (s.specialty == Student::Informatics) 
    {
        cout << "������ � ��������� ������: ";
        cin >> s.marks.informatics.numerics;
    }
    else 
    {
        cout << "������ � ���������: ";
        cin >> s.marks.otherSpecialty.pedagogy;
    }
}

void displayStudents(const vector<Student>& students) 
{
    cout << "�\t�������\t����\t������������\tԳ����\t����������\t�������������/������� ������/���������\n";
    int i = 1;
    for (const auto& student : students) 
    {
        cout << i++ << "\t" << student.lastName << "\t" << student.course << "\t";
        switch (student.specialty) 
        {
        case Student::ComputerScience: cout << "����'����� �����"; break;
        case Student::Informatics: cout << "�����������"; break;
        case Student::MathAndEconomics: cout << "���������� �� ��������"; break;
        case Student::PhysicsAndInformatics: cout << "Գ���� �� �����������"; break;
        case Student::LaborTraining: cout << "������� ��������"; break;
        }
        cout << "\t" << student.marks.compSci.physics << "\t" << student.marks.compSci.math;
        if (student.specialty == Student::ComputerScience) 
        {
            cout << "\t" << student.marks.compSci.programming;
        }
        else if (student.specialty == Student::Informatics) 
        {
            cout << "\t" << student.marks.informatics.numerics;
        }
        else 
        {
            cout << "\t" << student.marks.otherSpecialty.pedagogy;
        }
        cout << endl;
    }
}

bool compareStudents(const Student& s1, const Student& s2) 
{
    if (s1.course != s2.course) return s1.course < s2.course;
    int thirdMark1 = 0, thirdMark2 = 0;
    if (s1.specialty == Student::ComputerScience) 
    {
        thirdMark1 = s1.marks.compSci.programming;
        thirdMark2 = s2.marks.compSci.programming;
    }
    else if (s1.specialty == Student::Informatics) 
    {
        thirdMark1 = s1.marks.informatics.numerics;
        thirdMark2 = s2.marks.informatics.numerics;
    }
    else 
    {
        thirdMark1 = s1.marks.otherSpecialty.pedagogy;
        thirdMark2 = s2.marks.otherSpecialty.pedagogy;
    }

    if (thirdMark1 != thirdMark2) return thirdMark1 > thirdMark2; 
    return s1.lastName > s2.lastName; 
}

bool binarySearch(const vector<Student>& students, const string& lastName, int course, int mark) 
{
    int left = 0, right = students.size() - 1;
    while (left <= right) 
    {
        int mid = left + (right - left) / 2;
        const Student& student = students[mid];
        int thirdMark = 0;
        if (student.specialty == Student::ComputerScience) 
        {
            thirdMark = student.marks.compSci.programming;
        }
        else if (student.specialty == Student::Informatics) 
        {
            thirdMark = student.marks.informatics.numerics;
        }
        else 
        {
            thirdMark = student.marks.otherSpecialty.pedagogy;
        }

        if (student.lastName == lastName && student.course == course && thirdMark == mark) 
        {
            return true;
        }

        if (student.course < course || (student.course == course && thirdMark < mark) || (student.course == course && thirdMark == mark && student.lastName < lastName)) 
        {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return false;
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Student> students;
    int n;
    cout << "������ ������� ��������: ";
    cin >> n;

    for (int i = 0; i < n; ++i) 
    {
        Student s;
        inputStudent(s);
        students.push_back(s);
    }

    int choice;
    do 
    {
        cout << "\n����:\n";
        cout << "1. ������� ������ ��������\n";
        cout << "2. ��������� ��������\n";
        cout << "3. ���������� ��������� �����\n";
        cout << "4. �������� ����� ��������\n";
        cout << "0. �����\n";
        cout << "��� ����: ";
        cin >> choice;

        switch (choice) 
        {
        case 1:
            displayStudents(students);
            break;

        case 2:
            sort(students.begin(), students.end(), compareStudents);
            cout << "���������� ���������.\n";
            break;

        case 3:
            cout << "��������� �����:\n";
            for (int i = 0; i < students.size(); ++i) 
            {
                cout << i + 1 << " ";
            }
            cout << endl;
            break;

        case 4:
        {
            string lastName;
            int course, mark;
            cout << "������ ������� ��������: ";
            cin >> lastName;
            cout << "������ ����: ";
            cin >> course;
            cout << "������ ������ � �������� ��������: ";
            cin >> mark;

            if (binarySearch(students, lastName, course, mark)) 
            {
                cout << "������� ���������.\n";
            }
            else 
            {
                cout << "������� �� ���������.\n";
            }
        }
        break;

        case 0:
            cout << "�����.\n";
            break;

        default:
            cout << "������� ����!\n";
        }
    } while (choice != 0);

    return 0;
}
