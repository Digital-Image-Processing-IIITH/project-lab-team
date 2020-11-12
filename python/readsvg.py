from svgpathtools import svg2paths, wsvg, svg2paths2
from svgpathtools import disvg

paths, attributes, svg_attributes = svg2paths2('svg/woman.svg')

first = paths[0]
firstattribs = attributes[0]
print(first)
print(firstattribs['stroke'])

for i in paths:
    disvg(i)
disvg(paths)