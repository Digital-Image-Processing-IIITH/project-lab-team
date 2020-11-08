# Read SVG into a list of path objects and list of dictionaries of attributes
from svgpathtools import svg2paths, wsvg, svg2paths2
from svgpathtools import disvg

# Update: You can now also extract the svg-attributes by setting
# return_svg_attributes=True, or with the convenience function svg2paths2
paths, attributes, svg_attributes = svg2paths2('svg/woman.svg')

# Let's print out the first path object and the color it was in the SVG
# We'll see it is composed of two CubicBezier objects and, in the SVG file it
# came from, it was red
first = paths[0]
first_attribs = attributes[0]
print(first)
print(first_attribs['stroke'])

# wsvg(paths, attributes=attributes, svg_attributes=svg_attributes, filename='output1.svg')
for i in paths:
    disvg(i)
disvg(paths)