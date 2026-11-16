#include <iostream>
#include <limits>
#include <stdexcept>
#include "String.h"

static void skip_line()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static bool read_int(const char* prompt, int& value)
{
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            skip_line();
            return true;
        }
        if (std::cin.eof())
            return false;

        std::cin.clear();
        skip_line();
        std::cout << "Please enter an integer." << std::endl;
    }
}

static bool read_string(const char* prompt, String& s)
{
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> s)
            return true;
        if (std::cin.eof())
            return false;
        std::cin.clear();
        skip_line();
        std::cout << "String cannot be longer than " << MAX_LENGTH << " characters, please try again." << std::endl;
    }
}

static void print_menu()
{
    std::cout << std::endl;
    std::cout << "1 - input A, B, C" << std::endl;
    std::cout << "2 - expression: D = \"BSUIR \" + A + B - C + A(i, 1) + \" FCSIS\"" << std::endl;
    std::cout << "3 - assignments: A += B, C = D = A, self-assignment" << std::endl;
    std::cout << "4 - case: ++A, --A, A++, A--" << std::endl;
    std::cout << "5 - character and substring: A[i], A(from, count)" << std::endl;
    std::cout << "6 - comparison of A and B, then if (A < B) D = A + B, else D = A - B" << std::endl;
    std::cout << "7 - constructors: default, with parameter, copy" << std::endl;
    std::cout << "0 - exit" << std::endl;
    std::cout << "select action: ";
}

int main()
{
    std::cout << std::boolalpha;

    String a("Hello World");
    String b("lo");
    String c("e");
    String d;

    char action;
    do
    {
        print_menu();
        if (!(std::cin >> action))
            break;
        skip_line();

        try
        {
            switch (action)
            {
            case '1':
                if (!read_string("enter A: ", a) ||
                    !read_string("enter B: ", b) ||
                    !read_string("enter C: ", c))
                    return 0;
                break;

            case '2':
            {
                int i;
                if (!read_int("index of character A for A(i, 1): ", i))
                    return 0;
                d = "BSUIR " + a + b - c + a(i, 1) + " FCSIS";
                std::cout << "D = " << d << std::endl;
                break;
            }

            case '3':
            {
                std::cout << "A += B -> " << (a += b) << std::endl;
                std::cout << "C = D = A -> " << (c = d = a) << std::endl;

                String& same = a;   
                a = same;          
                std::cout << "A = A -> " << a << std::endl;
                break;
            }

            case '4':
            {
                std::cout << "++A -> " << ++a << std::endl;
                std::cout << "--A -> " << --a << std::endl;

                String before = a++;   
                std::cout << "A++ returned " << before << ", now A = " << a << std::endl;

                before = a--;
                std::cout << "A-- returned " << before << ", now A = " << a << std::endl;
                break;
            }

            case '5':
            {
                int i, from, count;
                char ch;

                if (!read_int("index for []: ", i))
                    return 0;
                std::cout << "A[" << i << "] = " << a[i] << std::endl;

                std::cout << "new character for this position: ";
                if (!(std::cin >> ch))
                    return 0;
                skip_line();
                a[i] = ch;  
                std::cout << "after assignment A = " << a << std::endl;

                if (!read_int("start index for (): ", from) ||
                    !read_int("substring length for (): ", count))
                    return 0;
                std::cout << "A(" << from << ", " << count << ") = " << a(from, count) << std::endl;
                break;
            }

            case '6':
                std::cout << "A < B:  " << (a < b) << std::endl;
                std::cout << "A > B:  " << (a > b) << std::endl;
                std::cout << "A <= B: " << (a <= b) << std::endl;
                std::cout << "A >= B: " << (a >= b) << std::endl;

                if (a < b)
                    d = a + b;
                else
                    d = a - b;
                std::cout << (a < b ? "A < B, so D = A + B = " : "A is not less than B, so D = A - B = ")
                    << d << std::endl;
                break;

            case '7':
            {
                String empty;                
                String text("constructor");  
                String copy(text);            
                copy += String(" copy");    

                std::cout << "default: \"" << empty << "\"" << std::endl;
                std::cout << "with parameter:   " << text << std::endl;
                std::cout << "copy after +=: " << copy << std::endl;
                std::cout << "original unchanged: " << text << std::endl;
                break;
            }

            case '0':
                std::cout << "exit" << std::endl;
                break;

            default:
                std::cout << "unknown action" << std::endl;
                break;
            }
        }
        catch (const std::out_of_range& e)
        {
            std::cout << "error: " << e.what() << std::endl;
        }

        std::cout << "A = " << a << std::endl;
        std::cout << "B = " << b << std::endl;
        std::cout << "C = " << c << std::endl;
        std::cout << "D = " << d << std::endl;
    } while (action != '0');

    return 0;
}