// COPYRTIGH_BEGIN
// COPYRIGHT_END

// Include Google Test header files.
#include "gtest/gtest.h"

// Include Magic Lantern header files.
#include "math/vector.h"

TEST(MlVector4Test, DefaultConstrutor) {
    // This test is named "DefaultConstructor", and belongs to the "MlVector4Test"
    // test case.

	MlVector4 *v = new MlVector4();

    EXPECT_TRUE(v != NULL);
}
