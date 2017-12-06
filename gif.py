#!/usr/bin/python3
from PIL import Image, ImageDraw

f = open("output/output.txt")
n, m, s = map(int, f.readline().split())

zoom = 4
for i in range(s):
    im = Image.new("RGB", (zoom*n, zoom*m))
    dr = ImageDraw.Draw(im)

    for j in range(n):
        line = f.readline()
        for k in range(m):
                if line[k]=='X':
                    dr.rectangle((j*zoom, k*zoom, (j+1)*zoom, (k+1)*zoom), (0, 0, 0))
                elif line[k]==' ':
                    dr.rectangle((j*zoom, k*zoom, (j+1)*zoom, (k+1)*zoom), (255, 255, 255))
                elif line[k]=='\n':
                    pass
                else:
                    raise Exception()
    im.save("output/out%03d.png" % i)
