#include "pch.h"
#include "../SimilarityChecker/SimilarityChecker.cpp"

TEST(SimilarityChecker, InvalidArgument) {
	SimilarityChecker similarityChecker;
	EXPECT_THROW(similarityChecker.getLengthCheckScore("A", ""), std::invalid_argument);
	EXPECT_THROW(similarityChecker.getLengthCheckScore("", "B"), std::invalid_argument);
}

TEST(SimilarityChecker, CheckLength) {
	SimilarityChecker similarityChecker;
	EXPECT_EQ(similarityChecker.getLengthCheckScore("ASD", "DSA"), 60);
	EXPECT_EQ(similarityChecker.getLengthCheckScore("A", "BB"), 0);
	EXPECT_EQ(similarityChecker.getLengthCheckScore("AAABB", "BAA"), 20);
	EXPECT_EQ(similarityChecker.getLengthCheckScore("AA", "AAA"), 30);
}
