The test task was to implement a function that returns the result of a mathematical expression. 

Task:
``````
#include <vector>

// TODO: Implement
float EvaluateExpression(const char* str)
{
	return 0.0f;
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
``````
