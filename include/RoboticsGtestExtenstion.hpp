// Standard headers
#include <limits>
#include <math.h>
// Gtest header
#include <gtest/gtest.h>

namespace RoboticsGtestExtension
{
  const double INF = sqrt(sqrt(std::numeric_limits<double>::max()));

  bool onSegment(const std::vector<double> p, const std::vector<double> q, const std::vector<double> r)
  {
    if (q[0] <= std::max(p[0], r[0]) && q[0] >= std::min(p[0], r[0]) && q[1] <= std::max(p[1], r[1]) &&
        q[1] >= std::min(p[1], r[1]))
      return true;
    return false;
  }

  // To find orientation of ordered triplet (p, q, r).
  // The function returns following values
  // 0 --> p, q and r are colinear
  // 1 --> Clockwise
  // 2 --> Counterclockwise
  int orientation(const std::vector<double> p, const std::vector<double> q, const std::vector<double> r)
  {
    double val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);

    if (val == 0)
      return 0;                // colinear
    return (val > 0) ? 1 : 2;  // clock or counterclock wise
  }

  // The function that returns true if line segment 'p1q1'
  // and 'p2q2' intersect.
  bool doIntersect(const std::vector<double> p1, const std::vector<double> q1, const std::vector<double> p2,
                   const std::vector<double> q2)
  {
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    std::cout << "Points:\n"
              << p1[0] << "; " << p1[1] << "\n"
              << q1[0] << "; " << q1[1] << "\n"
              << p2[0] << "; " << p2[1] << "\n"
              << q2[0] << "; " << q2[1] << "\n";
    std::cout << "Orientations:\n" << o1 << " " << o2 << " " << o3 << " " << o4 << "\n\n";

    // General case
    if (o1 != o2 && o3 != o4)
      return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1))
      return true;

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1))
      return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2))
      return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2))
      return true;

    return false;  // Doesn't fall in any of the above cases
  }

  testing::AssertionResult pointInPolygon(const std::vector<double> point,
                                          const std::vector<std::vector<double>> polygon)
  {
    // Source: https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
    // NB: Using coordinates greater than 1e77 may result in incorrect results.
    // There must be at least 3 vertices in polygon[]
    if (polygon.size() < 3)
      return testing::AssertionFailure() << "Point " << point[0] << ", " << point[1] << " not in polygon";

    // Create a point for line segment from p to infinite
    const std::vector<double> extreme = { INF, point[1] };

    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do
    {
      int next = (i + 1) % polygon.size();

      // Check if the line segment from 'p' to 'extreme' intersects
      // with the line segment from 'polygon[i]' to 'polygon[next]'
      if (doIntersect(polygon[i], polygon[next], point, extreme))
      {
        std::cout << "Do Intersect: " << i << "\n";
        // If the point 'p' is colinear with line segment 'i-next',
        // then check if it lies on segment. If it lies, return true,
        // otherwise false
        if (orientation(polygon[i], point, polygon[next]) == 0)
          if (onSegment(polygon[i], point, polygon[next]))
          {
            return testing::AssertionSuccess() << "Point " << point[0] << ", " << point[1] << " in polygon";
          }
          else
          {
            return testing::AssertionFailure() << "Point " << point[0] << ", " << point[1] << " not in polygon";
          }

        count++;
      }
      i = next;
    } while (i != 0);

    // Return true if count is odd, false otherwise
    if (count & 1)  // Same as (count%2 == 1)
    {
      return testing::AssertionSuccess() << "Point " << point[0] << ", " << point[1] << " in polygon";
    }
    return testing::AssertionFailure() << "Point " << point[0] << ", " << point[1] << " not in polygon";
  }

}  // namespace RoboticsGtestExtension
