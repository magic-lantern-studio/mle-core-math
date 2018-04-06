// COPYRTIGH_BEGIN
// COPYRIGHT_END

// Include Google Test header files.
#include "gtest/gtest.h"

// Include Magic Lantern header files.
#include "math/vector.h"

TEST(MlVector2Test, DefaultConstrutor) {
    // This test is named "DefaultConstructor", and belongs to the "MlVector2Test"
    // test case.

	MlVector2 *v = new MlVector2();

    EXPECT_TRUE(v != NULL);
}

TEST(MlVector2Test, InitConstrutor) {
    // This test is named "InitConstructor", and belongs to the "MlVector2Test"
    // test case.

	MlScalar x = 0;
	MlScalar y = 0;

	MlVector2 *v = new MlVector2(x, y);

    EXPECT_TRUE(v != NULL);
}
