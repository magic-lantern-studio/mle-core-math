// COPYRTIGH_BEGIN
// COPYRIGHT_END

// Include Google Test header files.
#include "gtest/gtest.h"

// Include Magic Lantern header files.
#include "math/vector.h"

TEST(MlVector3Test, DefaultConstrutor) {
    // This test is named "DefaultConstructor", and belongs to the "MlVector3Test"
    // test case.

	MlVector3 *v = new MlVector3();

    EXPECT_TRUE(v != NULL);
}
