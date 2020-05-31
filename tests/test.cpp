// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <thread>
int main(int argc, char *argv[]) {
    unsigned int m = std::thread::hardware_concurrency();
    if ((argc > 1) && (atoi(argv[1])))
        m = atoi(argv[1]);
    header::startTreads(m);
    return 0;
}

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}
