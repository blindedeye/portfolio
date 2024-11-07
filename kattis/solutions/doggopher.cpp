/*
Kattis - Dog & Gopher
Loop Lab
Updated By: Jake Peterson
CSCI 111
Date: 07-October-2022
Read and solve the Kattis problem: https://open.kattis.com/problems/doggopher
Algorithm Steps:
        1. Read gopher and dog's coordinates
        2. Define a function to find and return the Euclidean distance between the two points
    3. For each gopher hole coordinate:
      3.a find the distance between the gopher position and the hole
      3.b find the distance between the dog position and the hole
      4.c if the dog's distance is larger or equal to twice the distance of gopher,
          gopher can get away through that hole.
          4.c.1 Stop testing other holes.
    4. If no safe hole is found, the gopher cannot escape.
*/

#include <iostream>
#include <cassert>
#include <string>
#include <iomanip>
#include <cmath>
#include <sstream>
using namespace std;

float distance(const float x1, const float y1, const float x2, const float y2);

void testDistance();

#define TOLERANCE 1e-6

int main(int argc, char* argv[]) {
  if (argc == 2 and string(argv[1]) == string("test")) {
    testDistance(); // FIXME1: FIXED
  }
  else {
    float gopherX, gopherY;
    float dogX, dogY;
    float x, y;
    string answer = "The gopher cannot escape.";
    float gopher_dist, dog_dist=0;

    cin >> gopherX >> gopherY;
    cin >> dogX >> dogY; // FIXME2: FIXED
    while (cin >> x >> y) {
      gopher_dist = distance(gopherX, gopherY, x, y);
      dog_dist = distance(dogX, dogY, x, y); // FIXME3: FIXED
      if (dog_dist >= 2*gopher_dist) {
        ostringstream oss;
        oss << fixed << showpoint << setprecision(3);
        oss << "The gopher can escape through the hole at (" << x << "," << y << ").";
        answer = oss.str();
        break;
      }
    }
    cout << answer << endl;
  }
    return 0;
}

float distance(const float x1, const float y1, const float x2, const float y2) {
  float d = 0;
  double x = x1 - x2;
  double y = y1 - y2;

  d = pow(x, 2) + pow(y, 2); // FIXME4: FIXED
  d = sqrt(d);
    return d;
}

void testDistance() {
  float x1, y1, x2, y2, answer, expected;
  x1 = 1.000f;
  y1 = 1.000f;
  x2 = 2.000f;
  y2 = 2.000f;
  answer = distance(x1, y1, x2, y2);
  expected = 1.4142135623731;
  cout << fixed << showpoint << setprecision(3) << endl;
  cout << answer << " " << expected << endl;
  assert(abs(answer-expected) < TOLERANCE);

  x1 = 2.000f;
  y1 = 2.000f;
  x2 = 1.000f;
  y2 = 1.000f;
  answer = distance(x1, y1, x2, y2);
  expected = 1.4142135623731;
  cout << fixed << showpoint << setprecision(3) << endl;
  cout << answer << " " << expected << endl;
  assert(abs(answer-expected) < TOLERANCE); // FIXME5: FIXED

  x1 = 4.000f;
  y1 = 4.500f;
  x2 = 2.500f;
  y2 = 2.000f;
  answer = distance(x1, y1, x2, y2);
  expected = 2.915476;
  cout << fixed << showpoint << setprecision(3) << endl;
  cout << answer << " " << expected << endl;
  assert(abs(answer-expected) < TOLERANCE); // FIXME6: FIXED

  x1 = 40.000f;
  y1 = 55.000f;
  x2 = 25.000f;
  y2 = 80.000f;
  answer = distance(x1, y1, x2, y2);
  cout << answer;
  expected = 29.15476;
  cout << fixed << showpoint << setprecision(3) << endl;
  cout << answer << " " << expected << endl;
  assert(abs(answer-expected) < TOLERANCE); // FIXME7: FIXED
  cerr << "All test cases passed!\n";
}