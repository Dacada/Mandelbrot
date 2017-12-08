#!/usr/bin/python

import sys
import subprocess
from PIL import Image

height,width,x1,y1,x2,y2 = sys.argv[1:]

im = Image.new('L',(int(width),int(height)))

p = subprocess.Popen(['./plot_section',height,width,x1,y1,x2,y2],stdout=subprocess.PIPE)

out,_ = p.communicate()
l = [ord(c) for c in out]
im.putdata(l)
im.show()
