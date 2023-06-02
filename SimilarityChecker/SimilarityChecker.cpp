#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

#define MAX_ALPHABET_SIZE (26)

class SimilarityChecker
{
public:
	int getLengthCheckScore(const string& leftStr, const string& rightStr)
	{
		assertIllegalArgument(leftStr);
		assertIllegalArgument(rightStr);

		if (leftStr.length() == rightStr.length()) return MAX_LENGTH_CHECK_SCORE;
		if (leftStr.length() >= 2 * rightStr.length()) return 0;
		if (rightStr.length() >= 2 * leftStr.length()) return 0;

		return getLengthCheckPartialScore(leftStr, rightStr);
	}

	int getAlphabetCheckScore(const string& leftStr, const string& rightStr)
	{
		assertIllegalArgument(leftStr);
		assertIllegalArgument(rightStr);

		initLeftStringAlpshabet(leftStr);
		initRightStringAlpshabet(rightStr);
		
		return getAlphabetCheckScore();
	}

private:
	void assertIllegalArgument(const string& str)
	{
		if (str == "")
		{
			throw std::invalid_argument("글자를 입력해주세요");
		}

		for (char ch : str)
		{
			if (ch < 'A' || ch > 'Z') throw std::invalid_argument("입력은 알파벳 대문자만 가능합니다.");
		}
	}

	int getLengthCheckPartialScore(const string& leftStr, const string& rightStr)
	{
		const int gap = getLengthGap(leftStr, rightStr);
		const int shortStringLength = getShortStringLength(leftStr, rightStr);

		return (1 - ((double)gap / (double)shortStringLength)) * MAX_LENGTH_CHECK_SCORE;
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

	void initLeftStringAlpshabet(const string& str)
	{
		memset(leftStringAlphabet, 0, sizeof(int) * MAX_ALPHABET_SIZE);
		for (char ch : str) leftStringAlphabet[ch - 'A']++;
	}

	void initRightStringAlpshabet(const string& str)
	{
		memset(rightStringAlphabet, 0, sizeof(int) * MAX_ALPHABET_SIZE);
		for (char ch : str) rightStringAlphabet[ch - 'A']++;
	}

	int getAlphabetCheckScore()
	{
		const int totalCnt = getTotalUsedAlphabetCount();
		const int sameCnt = getSameUsedAlphabetCount();

		return ((double)sameCnt / (double)totalCnt) * MAX_ALPHABET_CHECK_SCORE;
	}

	int getTotalUsedAlphabetCount()
	{
		int cnt = 0;

		for (int i = 0;i < MAX_ALPHABET_SIZE; ++i)
		{
			if (leftStringAlphabet[i] || rightStringAlphabet[i])
				cnt++;
		}

		return cnt;
	}

	int getSameUsedAlphabetCount()
	{
		int cnt = 0;

		for (int i = 0;i < MAX_ALPHABET_SIZE; ++i)
		{
			if (leftStringAlphabet[i] && rightStringAlphabet[i]) 
				cnt++;
		}

		return cnt;
	}

private:
	const int MAX_LENGTH_CHECK_SCORE = 60;
	const int MAX_ALPHABET_CHECK_SCORE = 40;

	int leftStringAlphabet[MAX_ALPHABET_SIZE];
	int rightStringAlphabet[MAX_ALPHABET_SIZE];
};
