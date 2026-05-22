
// AdapterVisualDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AdapterVisual.h"
#include "AdapterVisualDlg.h"
#include "afxdialogex.h"

#include <memory>
#include <map>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

vector<shared_ptr<VectorObject>> vectorObjects {
  make_shared<VectorRectangle>(10,10,100,100),
  make_shared<VectorRectangle>(30,30,60,60)
};

struct LineToPointAdapter
{
private:
    Points points;
public:
  typedef vector<Point> Points;

  LineToPointAdapter(Line& line)
  {
    static int count = 0;
    TRACE("%d: Generating points for line (no caching)\n", count++);

    // no interpolation
    int left = min(line.start.x, line.end.x);
    int right = max(line.start.x, line.end.x);
    int top = min(line.start.y, line.end.y);
    int bottom = max(line.start.y, line.end.y);
    int dx = right - left;
    int dy = line.end.y - line.start.y;

    // only vertical or horizontal lines
    if (dx == 0)
    {
      // vertical
      for (int y = top; y <= bottom; ++y)
      {
        points.emplace_back(Point{ left,y });
      }
    }
    else if (dy == 0)
    {
      for (int x = left; x <= right; ++x)
      {
        points.emplace_back(Point{ x, top });
      }
    }
  }

  virtual Points::iterator begin() { return points.begin(); }
  virtual Points::iterator end() { return points.end(); }

};

// made it cache, so it can be changed during runtime

struct LineToPointCachingAdapter
{
  typedef vector<Point> Points;

  LineToPointCachingAdapter(Line& line)
  {
    boost::hash<Line> hash;
    line_hash = hash(line);
    if (cache.find(line_hash) != cache.end()) return;

    static int count = 0;
    TRACE("%d: Generating points for line (with caching)\n", count++);

    // no interpolation
    Points points;

    int left = min(line.start.x, line.end.x);
    int right = max(line.start.x, line.end.x);
    int top = min(line.start.y, line.end.y);
    int bottom = max(line.start.y, line.end.y);
    int dx = right - left;
    int dy = line.end.y - line.start.y;

    // only vertical or horizontal lines
    if (dx == 0)
    {
      // vertical
      for (int y = top; y <= bottom; ++y)
      {
        points.emplace_back(Point{ left,y });
      }
    }
    else if (dy == 0)
    {
      for (int x = left; x <= right; ++x)
      {
        points.emplace_back(Point{ x, top });
      }
    }

    cache[line_hash] = points;
  }

  virtual Points::iterator begin() { return cache[line_hash].begin(); }
  virtual Points::iterator end() { return cache[line_hash].end(); }
private:
  size_t line_hash;
  static map<size_t, Points> cache;
};

// ...
