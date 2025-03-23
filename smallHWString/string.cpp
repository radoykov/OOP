#include <iostream>
#include <cstring>

using namespace std;

class String
{
    char *data;
    size_t size;

public:
    /**
     * @brief Construct a new String object and it should have a default value of ""
     *
     */
    String()
    {
        data = new char[1];
        data[0] = '\0';
        size = 0;
    }

    /**
     * @brief Construct a new String object with the provided value
     *
     * @param str
     */
    String(const char *str)
    {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
        size = strlen(data);
    }

    /**
     * @brief Construct a new String object by copying another string
     *
     * @param other
     */
    String(const String &other)
        : String(other.data)
    {
    }

    /**
     * @brief Copies the values from the other string in this string
     *
     * @param other
     * @return String&
     */
    String &operator=(const String &other)
    {
        if (this != &other)
        {
            int len = strlen(other.data);
            this->size = len;
            delete[] this->data;
            this->data = new char[len + 1];
            strcpy(this->data, other.data);
        }

        return *this;
    }

    /**
     * @brief Inserts a character at the provided index, if the index is bigger than the size of the string, just return the string, withouth modifying it
     *
     * @param index
     * @param c
     * @return String&
     */
    String &insert(size_t index, char c)
    {
        if (index > this->size)
        {
            return *this;
        }

        char *temp = new char[++this->size + 1];
        strcpy(temp, this->data);

        for (int i = this->size - 1; i > index; i--)
        {
            temp[i] = temp[i - 1];
        }
        temp[index] = c;

        delete[] this->data;
        this->data = temp;

        return *this;
    }

    /**
     * @brief Replaces the character at the provided index, if the index is bigger than the size of the string, just return the string, withouth modifying it
     *
     * @param index
     * @param c
     * @return String&
     */
    String &replace(size_t index, char c)
    {
        if (index + 1 > this->size)
        {
            return *this;
        }
        this->data[index] = c;

        return *this;
    }

    /**
     * @brief Finds the first index, where the provided character is found, return -1 if the character is not found
     *
     * @param c
     * @return int
     */
    int findFirstOf(char c) const
    {
        for (int i = 0; this->data[i] != '\0'; i++)
        {
            if (this->data[i] == c)
            {
                return i;
            }
        }
        return -1;
    }

    /**
     * @brief Destroy the String object
     *
     */
    ~String()
    {
        delete[] data;
    }

    /**
     * @brief Returns the string as a C-style string - char*
     *
     * @return const char*
     */
    char *toCString() const
    {
        return data;
    }

    /**
     * @brief Returns the length of the string
     *
     * @return size_t
     */
    size_t length() const
    {
        return size;
    }

    /**
     * @brief Appends a character to the string
     *
     * @param ch
     */
    void append(char ch)
    {
        char *temp = new char[++this->size + 1];
        strcpy(temp, data);
        delete[] this->data;

        temp[this->size - 1] = ch;
        temp[size] = '\0';
        this->data = temp;
    }

    /**
     * @brief Append the provided string to the current string
     *
     * @param str
     */
    void concat(const char *str)
    {
        int size2 = strlen(str);
        char *temp = new char[this->size + size2 + 1];

        for (int i = 0; i < this->size ; i++)
        {
            temp[i] = this->data[i];
        }
        int k = 0;
        for (int i = this->size; i < this->size + size2 + 1; i++)
        {
            temp[i] = str[k++];
        }
        delete[] this->data;
        this->size += size2;
        this->data = temp;
    }

    /**
     * @brief Compares 2 strings
     *
     * @param other
     * @return int 0 if the strings are equal, 1 if the current string is greater, -1 if the current string is smaller
     */
    int compare(const String &other) const
    {
        return strcmp(this->data, other.data);
    }
};

// int main()
// {
//     String s("hello");
//     s.concat(" world");
//     cout << s.toCString();
//     // REQUIRE(strcmp(str.toCString(), "Hhello") == 0);

//     return 0;
// }

