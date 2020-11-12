from svgpathtools import wsvg, svg2paths2, disvg
from svgpathtools import Path, Line, QuadraticBezier, CubicBezier, Arc
from svgpathtools import disvg, parse_path

# class Grammar:
#     def __init__(self):
#         self.name = None
#         self.rules = None
#         self.seed = 0
#         self.random = None
#         self.rule_mapping = None
#         self.tag_mapping = None



def make_polyline_rect(A, B):
    minX = min(A[0], B[0])
    maxX = max(A[0], B[0])
    minY = min(A[1], B[1])
    maxY = max(A[1], B[1])

    seg1 = Line(minX + minY * 1j, maxX + minY * 1j)
    seg2 = Line(maxX + minY * 1j, maxX + maxY * 1j)
    seg3 = Line(maxX + maxY * 1j, minX + maxY * 1j)
    seg4 = Line(minX + maxY * 1j, minX + minY * 1j)
    return Path(seg1, seg2, seg3, seg4)

def append_paths(pathsList):
    path = Path()
    for i in pathsList:
        for j in i:
            path.append(j)
    return path

# Little squares
s5_1 = make_polyline_rect([350.0, -325.0], [400.0, -275.0])
s5_2 = make_polyline_rect([350.0, -225.0], [400.0, -175.0])
s5_3 = make_polyline_rect([350.0, -125.0], [400.0, -75.0])
s5_4 = make_polyline_rect([350.0, -25.0],  [400.0, 25.0])
s5_5 = make_polyline_rect([350.0, 75.0],   [400.0, 125.0])
s5_6 = make_polyline_rect([350.0, 175.0],  [400.0, 225.0])
s5_7 = make_polyline_rect([350.0, 275.0],  [400.0, 325.0])

# Medium squares
s1 = make_polyline_rect([-100.0, -100.0], [100.0, 100.0])
s2 = make_polyline_rect([-100.0, -100.0], [100.0, 100.0])  

# Big square
s3 = make_polyline_rect([-300.0, -300.0], [300.0, 300.0])

# disvg(s5_1)
# disvg(s5_2)
# disvg(s5_3)
# disvg(s5_4)
# disvg(s5_5)
# disvg(s5_6)
# disvg(s5_7)

# disvg(s1)
# disvg(s2)
# disvg(s3)


# Some tag nonsense is happening here

path = append_paths([s1, s2, s3, s5_1, s5_2, s5_3, s5_4, s5_5, s5_6, s5_7])
disvg(path)