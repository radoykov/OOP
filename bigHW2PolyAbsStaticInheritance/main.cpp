#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class EmployeeSalaries
{
    double *salaries;
    unsigned int size;
    unsigned int capacity;
    string employeeName;

    void resize()
    {
        capacity *= 2;
        double *arr = new double[capacity];
        for (unsigned int i = 0; i < size; i++)
        {
            arr[i] = salaries[i];
        }
        delete[] salaries;
        salaries = arr;
    }
    void setSize(const unsigned int size)
    {
        if (size <= 0)
        {
            throw invalid_argument("Error size must be positive!");
        }
        this->size = size;
    }

    void setCapacity(const unsigned int capacity)
    {
        if (capacity <= 0)
        {
            throw invalid_argument("Error capacity must be positive!");
        }
        this->capacity = capacity;
    }
    void salaryValidation(const double salary)
    {
        if (salary < 910.00 || salary > 2500.00)
        {
            throw invalid_argument("Error value for salaries must be between 910.00 - 2500.00!");
        }
    }

public:
    EmployeeSalaries()
    {
        size = 1;
        capacity = 2;
        salaries = new double[capacity];
        salaries[0] = 910.00;
        employeeName = "";
    }

    EmployeeSalaries(const double *salaries, const unsigned int size, const unsigned int capacity, const string &employeeName)
    {
        setSize(size);
        setCapacity(capacity);
        this->employeeName = employeeName;

        this->salaries = new double[this->size];

        for (unsigned int i = 0; i < this->size; i++)
        {
            salaryValidation(salaries[i]);
            this->salaries[i] = salaries[i];
        }
    }

    EmployeeSalaries(const EmployeeSalaries &other)
        : EmployeeSalaries(other.salaries, other.size, other.capacity, other.employeeName) {}

    EmployeeSalaries &operator=(const EmployeeSalaries &other)
    {
        if (this != &other)
        {
            setSize(other.size);
            setCapacity(other.capacity);
            this->employeeName = other.employeeName;

            delete[] this->salaries;
            this->salaries = new double[this->capacity];
            for (unsigned int i = 0; i < size; i++)
            {
                this->salaries[i] = other.salaries[i];
            }
        }

        return *this;
    }

    const double *getSalaries() const // to prevent outside manipulation
    {
        return salaries;
    }
    unsigned int getSize() const
    {
        return size;
    }
    unsigned int getCapacity() const
    {
        return capacity;
    }
    string getEmployeeName() const
    {
        return employeeName;
    }

    void addSalary(double salary)
    {
        if (size == capacity)
        {
            resize();
        }
        salaryValidation(salary);
        salaries[size++] = salary;
    }

    ~EmployeeSalaries()
    {
        delete[] salaries;
    }
};

class Person
{
    string name;
    unsigned int age;

    static unsigned int countOfPeople;

    // validation of name and age

    void setName(const string name)
    {
        if (name == "")
        {
            throw invalid_argument("Error name must not be empty!");
        }
        this->name = name;
    }
    void setAge(const unsigned int age)
    {
        if (age < 0 || age > 65)
        {
            throw invalid_argument("Error age must be within 0 - 65!");
        }
        this->age = age;
    }

public:
    Person()
    {
        countOfPeople++;
    }

    Person(const string &name, const unsigned int age)
    {
        setName(name);
        setAge(age);
        countOfPeople++;
    }

    Person(const Person &other)
        : Person(other.name, other.age) {}

    Person &operator=(const Person &other)
    {
        if (this != &other)
        {
            setName(other.name);
            setAge(other.age);
        }
        return *this;
    }

    string getName() const
    {
        return name;
    }
    unsigned int getAge() const
    {
        return age;
    }
    unsigned int getCountsOfPeople() const
    {
        return countOfPeople;
    }

    virtual ~Person()
    {
        countOfPeople--;
    }
};

class Employee : public Person
{
    EmployeeSalaries salaries;
    unsigned int experience;
    string position;

    void setExperience(const unsigned int experience)
    {
        if (experience < 1)
        {
            throw invalid_argument("Error experience must be above 1!");
        }
        this->experience = experience;
    }
    void setPosition(const string position)
    {
        if (position == "")
        {
            throw invalid_argument("Error position must not be empty!");
        }
        this->position = position;
    }

public:
    Employee() {}
    Employee(const string name, const unsigned int age, const EmployeeSalaries &salaries, const unsigned int experience, const string position)
        : Person(name, age)
    {
        this->salaries = salaries; // using operator=
        setExperience(experience);
        setPosition(position);
    }
    Employee(const Employee &other)
        : Employee(other.getName(), other.getAge(), other.salaries, other.experience, other.position) {}

    Employee &operator=(const Employee &other)
    {
        if (this != &other)
        {
            Person::operator=(other); // auto cast
            salaries = other.salaries;
            setExperience(other.experience);
            setPosition(other.position);
        }
        return *this;
    }

    EmployeeSalaries &getSalaries()
    {
        return salaries;
    }
    unsigned int getExperience() const
    {
        return experience;
    }
    string getPosition() const
    {
        return position;
    }

    double calculateAverageSalary()
    {
        const double *arr = this->salaries.getSalaries();
        unsigned int size = this->salaries.getSize();

        double sum = 0;
        for (unsigned int i = 0; i < size; i++)
        {
            sum += arr[i];
        }

        return sum / size;
    }
    friend ifstream &operator>>(ifstream &in, Employee &employee);
    friend ofstream &operator<<(ofstream &out, Employee &employee);
};

ifstream &operator>>(ifstream &in, Employee &employee)
{
    string firstName, lastName, position;
    unsigned int age, experience;
    EmployeeSalaries salaries;
    in >> firstName >> lastName >> age >> position >> experience;

    string fullName = firstName + " " + lastName;
    Employee employeeTemp(fullName, age, salaries, experience, position);

    employee = employeeTemp;

    return in;
}

ofstream &operator<<(ofstream &out, Employee &employee)
{
    out << employee.getName() << " "
        << employee.getPosition() << " "
        << employee.getExperience() << " "
        << employee.calculateAverageSalary() << " " << endl;

    return out;
}

class Manager : public Person
{
    string department;

    void setDepartment(const string department)
    {
        if (department.empty())
        {
            throw invalid_argument("Error department must not be empty!");
        }
        string arr[] = {"delivery", "marketing", "sales", "human resources"};

        for (int i = 0; i < arr->length(); i++)
        {
            if (arr[i] == department)
            {

                this->department = department;
                return;
            }
        }

        throw invalid_argument("Error this department do not exist. Please choose from these -  delivery, marketing, sales, human resources.!");
    }

public:
    Manager() {}
    Manager(const string &name, const unsigned int age, const string &department)
        : Person(name, age)
    {
        setDepartment(department);
    }

    Manager(const Manager &other)
        : Manager(other.getName(), other.getAge(), other.department) {}

    Manager &operator=(const Manager &other)
    {
        if (this != &other)
        {
            Person::operator=(other);
            this->department = other.department;
        }

        return *this;
    }

    string getDepartment() const
    {
        return department;
    }

    void payEmployeeByName(string &employeeName, vector<Employee> &employees, double salary)
    {
        for (Employee &employee : employees)
        {
            if (employee.getName() == employeeName)
            {
                EmployeeSalaries &es = employee.getSalaries();
                es.addSalary(salary);
                return;
            }
        }
        throw invalid_argument("Error emloyee does not exist!");
    }
    friend ifstream &operator>>(ifstream &in, Manager &manager);
    friend ofstream &operator<<(ofstream &out, Manager &manager);
};

ifstream &operator>>(ifstream &in, Manager &manager)
{
    string managerFirstName, managerLastName, department;
    double salary;
    unsigned int age;

    in >> managerFirstName >> managerLastName >> age >> department;

    string fullManagerName = managerFirstName + " " + managerLastName;

    Manager managerTemp(fullManagerName, age, department);

    manager = managerTemp;

    return in;
}

ofstream &operator<<(ofstream &out, Manager &manager)
{
    out << manager.getName() << " "
        << manager.getAge() << " "
        << manager.getDepartment() << endl;

    return out;
}

class FileManager
{
    const string input;
    const string output;

public:
    FileManager(const string &input, const string &output)
        : input(input), output(output) {}

    void read(vector<Employee> &employees, vector<Manager> &managers)
    {

        ifstream file(input);
        if (!file.is_open())
        {
            throw invalid_argument("Error opening file!");
            return;
        }
        string type;

        while (file >> type)
        {
            if (type == "e")
            {
                Employee emp;
                file >> emp;
                employees.push_back(emp);
            }
            else if (type == "m")
            {
                Manager mng;
                file >> mng;
                managers.push_back(mng);

                // paying
                string firstName, lastName, fullName;
                double salary;
                file >> firstName >> lastName >> salary;
                fullName = firstName + " " + lastName;

                mng.payEmployeeByName(fullName, employees, salary);
            }
        }

        file.close();
    }
    void write(vector<Employee> &employees, vector<Manager> &managers)
    {
        ofstream file(output, ios::out); // or app
        if (!file.is_open())
        {
            throw invalid_argument("Error opening file!");
            return;
        }
        for (auto &employee : employees)
        {
            file << employee;
        }
        file << endl;
        for (auto &manager : managers)
        {
            file << manager;
        }
        file.close();
    }
};

unsigned int Person::countOfPeople = 0;

int main()
{
    FileManager fManager("fileInput.txt", "fileOutput.txt");
    vector<Employee> employees;
    vector<Manager> managers;

    try
    {
        fManager.read(employees, managers);
        fManager.write(employees, managers);
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }

    return 0;
}