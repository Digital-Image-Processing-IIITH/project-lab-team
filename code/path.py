# Coordinates are given as points in the complex plane
from svgpathtools import Path, Line, QuadraticBezier, CubicBezier, Arc
from svgpathtools import parse_path
from svgpathtools import kinks, smoothed_path
from svgpathtools import disvg
from time import sleep


seg1 = CubicBezier(300 + 100j, 100 + 100j, 200 + 200j, 200 + 300j)  # A cubic beginning at (300, 100) and ending at (200, 300)
seg2 = Line(200 + 300j, 250 + 350j)  # A line beginning at (200, 300) and ending at (250, 350)
path = Path(seg1, seg2)  # A path traversing the cubic and then the line

# We could alternatively created this Path object using a d-string
path_alt = parse_path('M 300 100 C 100 100 200 200 200 300 L 250 350')

# Let's check that these two methods are equivalent
print(path)
print(path_alt)
print(path == path_alt)

# On a related note, the Path.d() method returns a Path object's d-string
print(path.d())
print(parse_path(path.d()) == path)

# Let's append another to the end of it
path.append(CubicBezier(250 + 350j, 275 + 350j, 250 + 225j, 200 + 100j))
print(path)

# Let's replace the first segment with a Line object
path[0] = Line(200 + 100j, 200 + 300j)
print(path)

# You may have noticed that this path is connected and now is also closed (i.e. path.start == path.end)
print("Path is continuous? ", path.iscontinuous())
print("Path is closed? ", path.isclosed())

# The curve the path follows is not, however, smooth (differentiable)
print("Path contains non-differentiable points? ", len(kinks(path)) > 0)

spath = smoothed_path(path)
print("Smooth path contains non-differentiable points? ", len(kinks(spath)) > 0)
print(spath)

# Let's take a quick look at the path and its smoothed relative
# The following commands will open two browser windows to display path and spaths
disvg(path)
sleep(1)  # needed when not giving the SVGs unique names (or not using timestamp)
disvg(spath)
print("Notice that path contains {} segments and smooth path contains {} segments."
      "".format(len(path), len(spath)))
