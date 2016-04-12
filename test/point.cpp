
#include <catch.hpp>

#include <stdexcept>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include <mann.h>

TEST_CASE("Point init", "[Point]") {
  using mann::Point;

  auto p = Point<double>{{1.0, 2.0}};
  CHECK(p[0] == Approx(1.0));
  CHECK(p[1] == Approx(2.0));

  auto p2 = Point<double>{{3.0, 4.0}};
  p[0] = 3.0;
  p[1] = 4.0;
  CHECK(p == p2);

  CHECK_THROWS_AS((Point<double>{{3.0, 4.0, 2.3}}), std::runtime_error);
}

TEST_CASE("Point from stream", "[Point]") {
  using mann::Point;

  std::istringstream input{"1.5 3.2\n4 2"};

  Point<double, 2> p;
  input >> p;
  CHECK(p[0] == Approx(1.5));
  CHECK(p[1] == Approx(3.2));

  Point<double, 2> p2;
  input >> p2;
  CHECK(p2[0] == Approx(4.0));
  CHECK(p2[1] == Approx(2.0));

  std::istringstream empty_input;
  CHECK_THROWS_AS(empty_input >> p, std::runtime_error);
}

TEST_CASE("Vector of Points", "[Point]") {
  using mann::Point;

  std::vector<Point<double, 2>> points;

  std::istringstream input{"1.5 3.2\n4 2\n0 1\n1 0\n"};

  while (!input.eof())
    if (input.peek() != EOF) points.emplace_back(input);

  CHECK(points.size() == 4);
  std::swap(points[0], points[2]);
  CHECK(points[0][1] == Approx(1.0));
  CHECK(points[2][0] == Approx(1.5));
}
