//Description: CHeader file for the class to represent the world and the items in it
#pragma once

#include "definitions.h"

struct WorldItem;

class World {
 public:
  World(int id);

  //non const -> return a reference to an element in position p, so can read and write the position of an element
  //used when want to modify the grid_
  inline uint8_t& at(const Point_Int& p) { return _grid[cols * p.x() + p.y()]; }

  //rturns a copy of the element at position p, so can only read the position of an element
  //used only when want to access the value the
  inline uint8_t at(const Point_Int& p) const { return _grid[cols * p.x() + p.y()]; }

  bool checkCollision(const Point_Int& p, const int radius) const;

  inline Point_Int world2grid(const Point& p) { return Point_Int(p.x() * i_res, p.y() * i_res); }

  inline Point grid2world(const Point_Int& p) { return Point(p.x() * res, p.y() * res); }

  inline bool inside(const Point_Int& p) const { return p.x() >= 0 && p.y() >= 0 && p.x() < rows && p.y() < cols; }

  void loadFromImage(const string filename_);

  bool traverseRay(Point_Int& endpoint, const Point_Int& origin, const float angle, const int max_range);

  void draw();

  void timeTick(float dt);
  
  void add(WorldItem* item);

  // only positive numbers for rows, cols and size
  unsigned int rows = 0, cols = 0, size = 0;
  float res = 0.05, i_res = 20.0;
  int _id = 0;
  
  cv::Mat display_image;

  vector<uint8_t> _grid;

  vector<WorldItem*> _items;
};

class WorldItem {
 public:
  WorldItem(World* w_, const Pose& p_ = Pose::Identity());
  
  WorldItem(WorldItem* parent_, const Pose& p_ = Pose::Identity());
  
  ~WorldItem();

  Pose poseInWorld();

  //no implementation in this class
  //pure virtual functions
  //used in derived classes
  virtual void draw() = 0;
  virtual void timeTick(float dt) = 0;

  World* world = nullptr;
  WorldItem* parent = nullptr;
  Pose pose_in_parent;
};
