from random import *;
from math import *;

inp = open("input.txt", 'r');
out = open("output.txt", 'w');
phrases = ["Sayonara!", "AstaLaVista", "VraguNeSdayotsyaNashGordyVaryag", "SeeYouInHell", "WarNeverChanges",
          "TakeItBoy!", "SoyuzNerushimyRespublikSvobodnyh", "EtoVamZaKenny", "ILoveLinal'sSmellInTheMorning"];
phrase = phrases[randint(0, len(phrases) - 1)];

v = [float(i) for i in inp.readline().split()]; #корабль
vx = v[0];
vy = v[1];

a = [float(i) for i in inp.readline().split()]; #киль
ax = a[0];
ay = a[1];

m = [float(i) for i in inp.readline().split()]; #мачта
mx = m[0];
my = m[1];

w = [float(i) for i in inp.readline().split()]; #враг
wx = w[0];
wy = w[1];


rel_x = wx - vx;
rel_y = wy - vy;

v_product = (ax * rel_y) - (ay * rel_x);
side = 0;
if (v_product > 0):
    side = 1;
elif (v_product < 0):
    side = -1;
else:
    side= 0;

nx = (ay ** 2 * wx - ax * ay * wy + ax ** 2 * vx + ax * ay * vy) / (ax ** 2 + ay ** 2) - vx;
ny = (ax ** 2 * wy - ax * ay * wx + ay ** 2 * vy + ax * ay * vx) / (ax ** 2 + ay ** 2) - vy;
if (nx == 0 and ny == 0):
    side = 0;
else:
    angle = (rel_x * ny - rel_y * nx) / (hypot(rel_x, rel_y) * hypot(nx, ny));
    angle = degrees(asin(angle));
    if (abs(angle) - 60 > 0.0000001):
        side = 0;
    else:
        angle *= side;

mast = degrees(atan(hypot(mx, my)));
if (mx * ay - my * ax > 0):
    mast = -mast;

if (side == 0):
    out.write(str(side) + '\n');
    out.write(str(phrase) + '\n');
else:
    out.write(str(side) + '\n');
    out.write(str(angle) + '\n');
    out.write(str(mast) + '\n');
    out.write(str(phrase) + '\n');

    
inp.close();
out.close();
