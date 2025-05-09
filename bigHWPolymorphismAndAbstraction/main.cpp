#include <iostream>
#include <cstring>
#include <exception>
#include <string>
#include <cmath>

enum OPERATIONS
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POWER,
    ROOT,
    INVALID
};

using namespace std;

class Operation
{
    string name;
    string symbol;

public:
    Operation() {}
    Operation(const string &name, const string &symbol)
    {
        setName(name);
        setSymbol(symbol);
    }

    Operation(const Operation &other)
        : Operation(other.name, other.symbol) {}

    Operation &operator=(const Operation &other)
    {
        if (this != &other)
        {
            this->name = other.name;
            this->symbol = other.symbol;
        }

        return *this;
    }

    virtual double execute(const double n1, const double n2) const = 0;

    void setName(const string &name)
    {
        if (name.empty())
        {
            throw invalid_argument("Name is empty!");
        }
        this->name = name;
    }
    void setSymbol(const string &symbol)
    {
        if (symbol.empty())
        {
            throw invalid_argument("Symbol is empty!");
        }
        this->symbol = symbol;
    }
    string getName() const
    {
        return name;
    }
    string getSymbol() const
    {
        return symbol;
    }
};

class AddOperation : public Operation
{

public:
    AddOperation() : Operation("add", "+") {}

    AddOperation(const AddOperation &other) : Operation(other) {}

    AddOperation &operator=(const AddOperation &other)
    {
        Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override
    {
        return n1 + n2;
    }
};

class SubstractOperation : public Operation
{

public:
    SubstractOperation() : Operation("substract", "-") {}

    SubstractOperation(const SubstractOperation &other) : Operation(other) {}

    SubstractOperation &operator=(const SubstractOperation &other)
    {
        Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override
    {
        return n1 - n2;
    }
};

class MultiplyOperation : public Operation
{

public:
    MultiplyOperation() : Operation("multiply", "*") {}

    MultiplyOperation(const MultiplyOperation &other) : Operation(other) {}

    MultiplyOperation &operator=(const MultiplyOperation &other)
    {
        Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override
    {
        return n1 * n2;
    }
};

class DivideOperation : public Operation
{

public:
    DivideOperation() : Operation("divide", "/") {}

    DivideOperation(const DivideOperation &other) : Operation(other) {}

    DivideOperation &operator=(const DivideOperation &other)
    {
        Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override
    {
        if (n2 == 0)
        {
            throw invalid_argument("Division by 0!");
        }
        return n1 / n2;
    }
};

class PowerOperation : public Operation
{

public:
    PowerOperation() : Operation("power", "**") {}

    PowerOperation(const PowerOperation &other) : Operation(other) {}

    PowerOperation &operator=(const PowerOperation &other)
    {
        Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override
    {
        double val = pow(n1, n2);

        if (isnan(val))
        {
            throw invalid_argument("Result of power operation is NaN (Not a Number)!");
        }
        else if (isinf(val))
        {
            throw invalid_argument("Result of power operation is Infinity!");
        }
        return val;
    }
};

class RootOperation : public Operation
{

public:
    RootOperation() : Operation("root", "V") {}

    RootOperation(const RootOperation &other) : Operation(other) {}

    RootOperation &operator=(const RootOperation &other)
    {
        Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override
    {
        if (n1 < 0 || n2 < 0)
        {
            throw invalid_argument("One of the root operation parameters is negative!");
        }
        double val = pow(n1, 1.0 / n2);

        if (isnan(val))
        {
            throw invalid_argument("Result of root operation is NaN (Not a Number)!");
        }
        else if (isinf(val))
        {
            throw invalid_argument("Result of root operation is Infinity!");
        }
        return val;
    }
};

class Calculator
{
    const char *name;
    size_t numberOfSupportedOperations;
    size_t capacityForOperations;
    Operation **operations;
    static double numberOfSuccessfullCalculations;

    void resizeCapacity()
    {
        this->capacityForOperations *= 2;
        Operation **newOps = new Operation *[this->capacityForOperations];

        for (size_t i = 0; i < this->numberOfSupportedOperations; i++)
        {
            newOps[i] = this->operations[i];
        }
        delete[] this->operations;
        this->operations = newOps;
    }

    void setName(const char *name)
    {
        if (strlen(name) == 0 || name == nullptr)
        {
            throw invalid_argument("Error: invalid name!");
        }
        char *newName = new char[strlen(name) + 1]; //!! +1 for '\0'
        strcpy(newName, name);
        this->name = newName;
    }

    Operation *createCopyOfOperation(const Operation *source)
    {
        return createOperation(source->getSymbol(), source->getName());
    }

public:
    Calculator()
        : capacityForOperations(2), numberOfSupportedOperations(0)
    {
        this->name = new char[13]{"Default name"};
        operations = new Operation *[capacityForOperations];
    }

    Calculator(const char *name, size_t n, Operation **ops)
    {
        setName(name);
        if (n <= 0)
        {
            throw invalid_argument("Error: non-positive size!");
        }
        if (ops == nullptr)
        {
            throw invalid_argument("Error: ops is nullptr!");
        }
        capacityForOperations = n * 2;
        numberOfSupportedOperations = n;

        operations = new Operation *[capacityForOperations];
        for (size_t i = 0; i < n; i++)
        {
            this->operations[i] = createCopyOfOperation(ops[i]);
        }
    }

    Calculator(const Calculator &other)
        : Calculator(other.name, other.numberOfSupportedOperations, other.operations) {}

    const Calculator &operator=(const Calculator &other)
    {
        if (this != &other)
        {
            delete[] this->name;
            setName(other.name);
            this->numberOfSupportedOperations = other.numberOfSupportedOperations;
            this->capacityForOperations = other.capacityForOperations;

            // deleting unnecessary memory
            freeOperationsMemory(operations, numberOfSupportedOperations);

            // filling in data
            this->operations = new Operation *[this->capacityForOperations];
            for (size_t i = 0; i < this->numberOfSupportedOperations; i++)
            {
                this->operations[i] = createCopyOfOperation(other.operations[i]);
            }
        }

        return *this;
    }

    ~Calculator()
    {
        delete[] name;
        freeOperationsMemory(operations, numberOfSupportedOperations);
    }

    void listSupportedOperations()
    {
        for (size_t i = 0; i < numberOfSupportedOperations; i++)
        {
            cout << operations[i]->getSymbol() << " - " << operations[i]->getName() << endl;
        }
    }

    void listInputFormat()
    {
        cout << "<num1>  <symbol>  <num2> … <numN> = \n";
    }

    Calculator &addOperation(const Operation *op)
    {
        if (capacityForOperations == numberOfSupportedOperations)
        {
            resizeCapacity();
        }
        this->operations[numberOfSupportedOperations] = createCopyOfOperation(op);
        numberOfSupportedOperations++;

        return *this;
    }

    void startCalculation()
    {
        cout << "Plese enter expression: " << endl;
        double a, b;
        string symbol;
        cin >> a >> symbol >> b;
        while (true)
        {
            for (size_t i = 0; i < numberOfSupportedOperations; i++)
            {
                if (operations[i]->getSymbol() == symbol)
                {
                    try
                    {
                        a = operations[i]->execute(a, b);
                    }
                    catch (const exception &e)
                    {
                        cout << e.what() << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        return;
                    }
                    break;
                }
            }

            cin >> symbol;
            if (symbol == "=")
            {
                break;
            }
            cin >> b;
        }
        cout << a << endl;
        numberOfSuccessfullCalculations++;
    }

    size_t getNumberOfSuccessfulCalculations() const
    {
        return numberOfSuccessfullCalculations;
    }

    static Operation *createOperation(const string symbol, const string name)
    {
        Operation *op;
        switch (getValidOperationName(symbol))
        {
        case ADD:
            op = new AddOperation();
            op->setName(name);
            return op;
        case SUBTRACT:
            op = new SubstractOperation();
            op->setName(name);
            return op;
        case MULTIPLY:
            op = new MultiplyOperation();
            op->setName(name);
            return op;
        case DIVIDE:
            op = new DivideOperation();
            op->setName(name);
            return op;
        case POWER:
            op = new PowerOperation();
            op->setName(name);
            return op;
        case ROOT:
            op = new RootOperation();
            op->setName(name);
            return op;
        default:
            throw invalid_argument("Error: invalid operation!");
        }
    }
    static OPERATIONS getValidOperationName(string str)
    {
        if (str == "+")
            return ADD;
        else if (str == "-")
            return SUBTRACT;
        else if (str == "*")
            return MULTIPLY;
        else if (str == "/")
            return DIVIDE;
        else if (str == "**")
            return POWER;
        else if (str == "V")
            return ROOT;
        else
            return INVALID;
    }

    static void freeOperationsMemory(Operation **ops, size_t numberOfSupportedOperations)
    {
        for (size_t i = 0; i < numberOfSupportedOperations; i++)
        {
            delete ops[i];
        }
        delete[] ops;
    }
};

double Calculator::numberOfSuccessfullCalculations = 0;

int main()
{
    char name[100];
    size_t numberOfOperations;

    cout << "Enter calculator’s name: ";
    cin >> name;
    cout << endl;
    cout << "Enter number of operations: ";
    cin >> numberOfOperations;

    Operation **ops = new Operation *[numberOfOperations];
    string currName, currSymbol, inputLine;
    for (size_t i = 0; i < numberOfOperations; i++)
    {
        cout << "Enter oper.<sign>-<name>" << endl;
        cin >> inputLine;
        size_t index = inputLine.find("-", 1);
        currSymbol = inputLine.substr(0, index);
        currName = inputLine.substr(index + 1, inputLine.size());

        try
        {
            Calculator::getValidOperationName(currSymbol);
            ops[i] = Calculator::createOperation(currSymbol, currName);
        }
        catch (const exception &e)
        {
            cout << e.what() << '\n';
            i--;
        }
    }
    Calculator *calc = new Calculator(name, numberOfOperations, ops);
    Calculator::freeOperationsMemory(ops, numberOfOperations);

    int option;
    while (true)
    {
        cout << "1.List supported Operations" << endl;
        cout << "2.List input format" << endl;
        cout << "3.Start calculation" << endl;
        cout << "4.Exit" << endl;
        cout << "Enter option: " << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            calc->listSupportedOperations();
            break;
        case 2:
            calc->listInputFormat();
            break;
        case 3:
            calc->startCalculation();
            break;
        case 4:
            cout << "The program have just finished." << endl;
            return 0;
            break;

        default:
            cout << "Error: invalid option!" << endl;
            break;
        }
    }

    return 0;
}

// For tests
/*
int main()
{
Calculator *calc = new Calculator();
AddOperation *addOp = new AddOperation();
SubstractOperation *subOp = new SubstractOperation();
RootOperation *rootOp = new RootOperation();

calc->addOperation(subOp);
calc->addOperation(addOp);
calc->addOperation(rootOp);

Calculator *calc2 = new Calculator(*calc);
Calculator *calc3 = calc2;
calc3->startCalculation();
cout << "successfull:" << calc->getNumberOfSuccessfulCalculations() << endl;
calc2->startCalculation();
cout << "successfull:" << calc->getNumberOfSuccessfulCalculations() << endl;

}
*/