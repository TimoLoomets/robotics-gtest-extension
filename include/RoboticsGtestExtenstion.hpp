// Standard headers
#include <limits>
// Gtest header
#include <gtest/gtest.h>

namespace RoboticsGtestExtension
{
  bool onSegment(const double p[2], const double q[2], const double r[2])
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
  int orientation(const double p[2], const double q[2], const double r[2])
  {
    int val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);

    if (val == 0)
      return 0;                // colinear
    return (val > 0) ? 1 : 2;  // clock or counterclock wise
  }

  // The function that returns true if line segment 'p1q1'
  // and 'p2q2' intersect.
  bool doIntersect(const double p1[2], const double q1[2], const double p2[2], const double q2[2])
  {
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

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

  testing::AssertionResult pointInPolygon(const std::vector<const double[2]> polygon, const double point[2])
  {
    // Source: https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
    // There must be at least 3 vertices in polygon[]
    if (polygon.size() < 3)
      return testing::AssertionFailure() << "Point " << point[0] << ", " << point[1] << " not in polygon";

    // Create a point for line segment from p to infinite
    const double extreme[2] = { std::numeric_limits<double>::max(), point[1] };

    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do
    {
      int next = (i + 1) % polygon.size();

      // Check if the line segment from 'p' to 'extreme' intersects
      // with the line segment from 'polygon[i]' to 'polygon[next]'
      if (doIntersect(polygon[i], polygon[next], point, extreme))
      {
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
