//
//  shape.hpp
//  tinygrammar
//
//  Created by tangles on 6/10/16.
//  Copyright © 2016 visgraph. All rights reserved.
//

#ifndef shape_h
#define shape_h

#include "common.h"

using namespace std;

// |=====================================|
// |======= BASIC SHAPES and META =======|
// |=====================================|


struct Shape {
    int shape_type = basic_shape;
    ~Shape() {};
};

struct ShapeGroup : vector<Shape*> {
    // inheriting constructors
    using vector<Shape*>::vector;
};

struct PartitionShapeGroup {
    ShapeGroup match;
    ShapeGroup added;
    ShapeGroup remainder;
};


// |=====================================|
// |======== SHAPES for TANGLES =========|
// |=====================================|

struct polyline2r : vector<ym_vec2r> {
    using vector<ym_vec2r>::vector;
};

// python-like list and dictionary manipulation
inline polyline2r operator+(const polyline2r& a, const polyline2r& b) { auto ret = polyline2r(); ret.insert(ret.end(),a.begin(),a.end()); ret.insert(ret.end(),b.begin(),b.end()); return ret; }
inline polyline2r operator+(const polyline2r& a, const ym_vec2r& b) { auto ret = polyline2r(); ret.insert(ret.end(),a.begin(),a.end()); ret.push_back(b); return ret; }

inline polyline2r& operator+=(polyline2r& a, const polyline2r& b) { a.insert(a.end(),b.begin(),b.end()); return a; }
inline polyline2r& operator+=(polyline2r& a, const ym_vec2r& b) { a.push_back(b); return a; }

struct polygon2r : vector<polyline2r> {
    using vector<polyline2r>::vector;
};

struct TangleShape : Shape {
    // grammar
    int                     tag = 0;
    int                     gid = 0;
    int                     tid = 0;
    
    // tangle shape
    ym_frame2r              frame = ym_identity_frame2r;
    polygon2r               poly;
    
    // guideline
    polyline2r              guideline;
    
    // drawing properties
    bool                    invert = false;
    
    TangleShape() {shape_type = tangle_shape;};
    TangleShape(int tag, int gid, int tid, const ym_frame2r& frame, const polygon2r& poly) : tag(tag), gid(gid), tid(tid), frame(frame), poly(poly) {shape_type = tangle_shape;};
    
    static int next_gid() {
        static int gid = 0;
        return ++gid;
    }
};

struct AnnotatedShape : Shape {
    // grammar
    int                     tag = 0;
    int                     gid = 0;
    int                     tid = 0;
    
    // tangle shape
    ym_frame2f              frame = ym_identity_frame2f;
    polygon2r               poly;
    
    Shape*                  annotation;
    
    AnnotatedShape() {shape_type = annotated_shape;};
};

#endif /* shape_h */
