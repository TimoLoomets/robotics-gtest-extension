// Gtest header
#include <gtest/gtest.h>
// Tested Header
#include <RoboticsGtestExtenstion.hpp>

TEST(PointInPolygon, PointInSquare)
{
  std::vector<double> point{ 0, 0 };
  std::vector<std::vector<double>> polygon{ { -1, -1 }, { -1, 1 }, { 1, 1 }, { 1, -1 } };
  ASSERT_TRUE(RoboticsGtestExtension::pointInPolygon(point, polygon));
}

TEST(PointInPolygon, PointLeftSquare)
{
  std::vector<double> point{ -2, 0 };
  std::vector<std::vector<double>> polygon{ { -1, -1 }, { -1, 1 }, { 1, 1 }, { 1, -1 } };
  ASSERT_FALSE(RoboticsGtestExtension::pointInPolygon(point, polygon));
}

TEST(PointInPolygon, PointRightSquare)
{
  std::vector<double> point{ 2, 0 };
  std::vector<std::vector<double>> polygon{ { -1, -1 }, { -1, 1 }, { 1, 1 }, { 1, -1 } };
  ASSERT_FALSE(RoboticsGtestExtension::pointInPolygon(point, polygon));
}

TEST(PointInPolygon, PointUpSquare)
{
  std::vector<double> point{ 0, 2 };
  std::vector<std::vector<double>> polygon{ { -1, -1 }, { -1, 1 }, { 1, 1 }, { 1, -1 } };
  ASSERT_FALSE(RoboticsGtestExtension::pointInPolygon(point, polygon));
}

TEST(PointInPolygon, PointDownSquare)
{
  std::vector<double> point{ 0, -2 };
  std::vector<std::vector<double>> polygon{ { -1, -1 }, { -1, 1 }, { 1, 1 }, { 1, -1 } };
  ASSERT_FALSE(RoboticsGtestExtension::pointInPolygon(point, polygon));
}

TEST(PointInPolygon, PointOutsideCenterU)
{
  std::vector<double> point{ 0, 0 };
  std::vector<std::vector<double>> polygon{ { -1, -1 },    { 1, -1 },      { 1, 1 },    { 0.5, 1 },
                                            { 0.5, -0.5 }, { -0.5, -0.5 }, { -0.5, 1 }, { -1, 1 } };
  ASSERT_FALSE(RoboticsGtestExtension::pointInPolygon(point, polygon));
}

TEST(PointInPolygon, PointInLeftU)
{
  std::vector<double> point{ -0.75, 0 };
  std::vector<std::vector<double>> polygon{ { -1, -1 },    { 1, -1 },      { 1, 1 },    { 0.5, 1 },
                                            { 0.5, -0.5 }, { -0.5, -0.5 }, { -0.5, 1 }, { -1, 1 } };
  ASSERT_TRUE(RoboticsGtestExtension::pointInPolygon(point, polygon));
}

TEST(PointInPolygon, PointInRightU)
{
  std::vector<double> point{ 0.75, 0 };
  std::vector<std::vector<double>> polygon{ { -1, -1 },    { 1, -1 },      { 1, 1 },    { 0.5, 1 },
                                            { 0.5, -0.5 }, { -0.5, -0.5 }, { -0.5, 1 }, { -1, 1 } };
  ASSERT_TRUE(RoboticsGtestExtension::pointInPolygon(point, polygon));
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}