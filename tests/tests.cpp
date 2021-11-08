// Copyright 2021 Your Name <your_email>

#include <gtest/gtest.h>

#include <shared_ptr.hpp>

TEST(First, Constructor) {
  SharedPtr<int> ptr1(new int(1337));
  SharedPtr<int> ptr2(ptr1);
  SharedPtr<int> ptr3 = ptr1;
  EXPECT_EQ(ptr1.use_count(), 3);
  EXPECT_EQ(ptr2.use_count(), 3);
  EXPECT_EQ(ptr3.use_count(), 3);
}

TEST(Second, Swap) {
  SharedPtr<int> ptr_1(new int(1337));
  SharedPtr<int> ptr_2(new int(228));
  ptr_1.swap(ptr_2);
  EXPECT_EQ(*ptr_1, 228);
  EXPECT_EQ(*ptr_2.get(), 1337);
}

TEST(Third, Bool) {
  SharedPtr<int> ptr1(new int(1337));
  SharedPtr<int> ptr2;
  EXPECT_FALSE(bool(ptr2));
  EXPECT_TRUE(bool(ptr1));
}

TEST(Fourth, Get) {
  int* p = new int(1337);
  SharedPtr<int> ptr(p);
  EXPECT_EQ(p, ptr.get());
}

TEST(Fifth, Reset) {
  SharedPtr<int> ptr1(new int(1337));
  SharedPtr<int> ptr2(ptr1);
  SharedPtr<int> ptr3 = ptr2;
  SharedPtr<int> ptr4(ptr1);
  ptr3.reset();
  ptr4.reset(new int(228));
  EXPECT_EQ(ptr1.use_count(), 2);
  EXPECT_EQ(ptr2.use_count(), 2);
  EXPECT_EQ(ptr3.get(), nullptr);
  EXPECT_EQ(ptr4.use_count(), 1);
  EXPECT_EQ(*ptr4, 228);
}
