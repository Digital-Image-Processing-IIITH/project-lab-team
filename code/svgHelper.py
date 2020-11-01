from svg import Parser, Rasterizer, SVG
from PIL import Image  
import sys

filename = 'woman'

svg = Parser.parse_file(filename + '.svg')
print('Image is {} by {}.'.format(svg.width, svg.height))

R = Rasterizer()
buffer = R.rasterize(svg, svg.width, svg.height)
print(sys.getsizeof(svg))
image = Image.frombytes('RGBA', (svg.width, svg.height), buffer)
image.save(filename + '.png') 