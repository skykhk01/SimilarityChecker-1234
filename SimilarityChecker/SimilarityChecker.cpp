#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class SimilarityChecker
{
public:
	int getLengthCheckScore(const string& leftStr, const string& rightStr)
	{
		assertIllegalArgument(leftStr, rightStr);

		if (leftStr.length() == rightStr.length()) return MAX_LENGTH_CHECK_SCORE;
		if (leftStr.length() >= 2 * rightStr.length()) return 0;
		if (rightStr.length() >= 2 * leftStr.length()) return 0;

		return getPartialScore(leftStr, rightStr);
	}

private:
	void assertIllegalArgument(const string& leftStr, const string& rightStr)
	{
		if (leftStr == "" || rightStr == "")
		{
			throw std::invalid_argument("글자를 입력해주세요");
		}
	}

	int getLengthGap(const string& leftStr, const string& rightStr)
	{
		if (leftStr.length() > rightStr.length()) 
			return leftStr.length() - rightStr.length();

		return rightStr.length() - leftStr.length();
	}

	int getShortStringLength(const string& leftStr, const string& rightStr)
	{
		if (leftStr.length() > rightStr.length()) 
			return rightStr.length();

		return leftStr.length();
	}

	int getPartialScore(const string& leftStr, const string& rightStr)
	{
		int gap = getLengthGap(leftStr, rightStr);
		int shortStringLength = getShortStringLength(leftStr, rightStr);

		return (1 - ((double)gap / (double)shortStringLength)) * MAX_LENGTH_CHECK_SCORE;
	}

private:
	const int MAX_LENGTH_CHECK_SCORE = 60;
};