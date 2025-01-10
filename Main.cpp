#include <vector>
#include <stack>
#include <string>
#include <stdexcept>

float Calculate(float a, float b, char math_operator)
{
    switch (math_operator)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0.0f) { throw std::runtime_error("Division by zero"); };
        return a / b;
    default:
        throw std::invalid_argument("Incorrect expression");
    }
}

int GetPriority(char math_operator)
{
    if (math_operator == '+' || math_operator == '-')
        return 1;
    if (math_operator == '*' || math_operator == '/')
        return 2;

    return 0;
}


float EvaluateExpression(const char* str)
{
    std::stack<char> math_operators;
    std::stack<float> values;

    try
    {
        for (int i = 0; str[i] != '\0';)
        {
            //skip space
            if (isspace(str[i]))
            {
                i++;
            }
            //gets value to values
            else if (isdigit(str[i]) || str[i] == '.')
            {
                int start_i = i;
                while (isdigit(str[i]) || str[i] == '.')
                {
                    i++;
                }
                values.push(std::stof(std::string(&str[start_i], i - start_i)));
            }
            //gets '(' to math operators
            else if (str[i] == '(')
            {
                math_operators.push(str[i]);
                i++;
            }
            //Converting expressions in parantheses to values in stack
            else if (str[i] == ')')
            {
                while (!math_operators.empty() && math_operators.top() != '(') //checks if math_operators is not empty, and if top operator in stack != '('
                {

                    char math_operarion = math_operators.top(); //gets top operator
                    math_operators.pop();

                    float b = values.top(); //gets top value to b
                    values.pop();

                    float a = values.top(); //gets top value to a
                    values.pop();

                    values.push(Calculate(a, b, math_operarion)); //adds new value to stack
                }
                if (!math_operators.empty() && math_operators.top() == '(')  //cleans stack from '('
                {
                    math_operators.pop();
                }
                i++;
            }
            //Calculates expression if current symbol has <= priority
            else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
            {
                while (!math_operators.empty() && GetPriority(math_operators.top()) >= GetPriority(str[i])) //Checks if expression has priority
                {
                    char math_operation = math_operators.top();
                    math_operators.pop();

                    float b = values.top();
                    values.pop();

                    float a = values.top();
                    values.pop();

                    values.push(Calculate(a, b, math_operation));
                }
                math_operators.push(str[i]); //adds currrent symbol to stack
                i++;
            }
            else
            {
                throw std::invalid_argument("Invalid character in expression");
            }
        }

        while (!math_operators.empty())
        {
            char math_operator = math_operators.top();
            math_operators.pop();

            float b = values.top();
            values.pop();

            float a = values.top();
            values.pop();

            values.push(Calculate(a, b, math_operator));
        }

        return values.top();
    }
    catch (const std::exception& exception)
    {
        printf("\033[31m\n[Error: %s]\n\033[0m", exception.what());
        return 0;
    }
}

int main()
{
    std::vector<const char*> Expressions =
    {
        "1+2+3+4+5",
        "1 + (2 + 3)/4",
        "(1 + (2 + 3)/4) * ((5-6) / 3)",
        "9/8/7/6/5/4/3/2/1"
    };

    // Additional points: do not use dynamic memory allocations

    for (const char* Expression : Expressions)
    {
        printf("Expression: %s, Evaluation Result: %f\n", Expression, EvaluateExpression(Expression));
    }
}
