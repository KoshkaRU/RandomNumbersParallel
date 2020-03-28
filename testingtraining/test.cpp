#include "pch.h"
#include "../ConsoleApplication1/TestRecord.h"
#include <unordered_set>


TEST(grouptestname, test1) {	

	std::unordered_set <test_record> myrecordsset;

	test_record a{ 1, "one" }, b{ 2, "two" };

    EXPECT_NO_THROW(myrecordsset.insert(a); );

	EXPECT_NO_THROW(myrecordsset.insert(b); );
		
}

