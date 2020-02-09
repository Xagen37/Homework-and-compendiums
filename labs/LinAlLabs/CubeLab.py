import math

inp = open("input.txt", 'r');
out = open("output.txt", 'w');

class Vector:
    def __init__(self, x, y, z):
        self.x, self.y, self.z = x, y, z;

    def add_vec(self, vec):
        return Vector(self.x + vec.x, self.y + vec.y, self.z + vec.z);

    def sub_vec(self, vec):
        return Vector(self.x - vec.x, self.y - vec.y, self.z - vec.z);

    def scal_mul_vec(self, vec):
        return self.x * vec.x + self.y * vec.y + self.z * vec.z;

    def mul_const(self, const):
        return Vector(self.x * const, self.y * const, self.z * const);

    def length(self):
        return math.sqrt(self.x**2 + self.y**2 + self.z**2);

    def norma(self):
        return self.mul_const(1 / self.length());



class Ray_of_hope:
    def __init__(self, point, vector, energy):
        self.point, self.vector, self.energy = point, vector, energy;

    def rifle(self, plane):
        if (self.energy == 0):
            return False;
        self.energy -= 1;
        self.point = plane.cross(self);
        n = plane.perp();
        proj = n.mul_const(self.vector.scal_mul_vec(n) / n.length());
        self.vector = self.vector.sub_vec(proj).mul_const(2).sub_vec(self.vector);
        return True;



class Plane:
    def __init__(self, p1, p2, p3):
        self.a, self.b, self.c = p1, p2, p3;
        self.A = p1.y * (p2.z - p3.z) + p2.y * (p3.z - p1.z) + p3.y*(p1.z - p2.z);
        self.B = p1.z * (p2.x - p3.x) + p2.z * (p3.x - p1.x) + p3.z*(p1.x - p2.x);
        self.C = p1.x * (p2.y - p3.y) + p2.y * (p3.y - p1.y) + p3.y*(p1.y - p2.y);
        self.D = -(p1.x * (p2.y * p3.z - p3.y * p2.z) + p2.x * (p3.y*p1.z - p1.y * p3.z) + p3.x * (p1.y * p2.z - p2.y * p1.z));

    def perp(self):
        return Vector(self.A, self.B, self.C).norma();

    def cross(self, ray):
        if (self.A * ray.vector.x + self.B * ray.vector.y + self.C * ray.vector.z == 0):
            return None;

        tmp = -(self.D + self.A * ray.point.x + self.B * ray.point.y + self.C * ray.point.z) \
              / (self.A * ray.vector.x + self.B * ray.vector.y + self.C * ray.vector.z);
        if (tmp < 0):
            return None;
        return ray.vector.mul_const(tmp).add_vec(ray.point);


a = [float(i) for i in inp.readline().split()]; 
A = Vector(a[0], a[1], a[2]);

b = [float(i) for i in inp.readline().split()]; 
B = Vector(b[0], b[1], b[2]);

c = [float(i) for i in inp.readline().split()]; 
C = Vector(c[0],c[1], c[2]);

d = [float(i) for i in inp.readline().split()]; 
D = Vector(d[0], d[1], d[2]);

norm = [float(i) for i in inp.readline().split()]; 
N = Vector(norm[0], norm[1], norm[2]);

point = [float(i) for i in inp.readline().split()]; 
P = Vector(point[0], point[1], point[2]);

energy = int(inp.readline());

ray = Ray_of_hope(P, N, energy);
cube = [Plane(A, B, C), Plane(B, C, D), Plane(A, B, D.add_vec(B).sub_vec(C)), Plane(A, C.add_vec(A).sub_vec(B), D.add_vec(A).sub_vec(B)), Plane(C, D, A.add_vec(C).sub_vec(B)), Plane(D, A.add_vec(D).sub_vec(C), B.add_vec(D).sub_vec(C))];
m = int(inp.readline());
mirror = [];
for i in range (m):
    x = [float(u) for u in inp.readline().split()];
    X = Vector(x[0], x[1], x[2]);
    y = [float(u) for u in inp.readline().split()];
    Y = Vector(y[0], y[1], y[2]);
    z = [float(u) for u in inp.readline().split()];
    Z = Vector(z[0], z[1], z[2]);
    mirror.append(Plane(X, Y, Z));

while True:
    #print("kek");
    cross_cube = None;
    for plane in cube:
        p = plane.cross(ray);
        if (p is not None and p.sub_vec(ray.point).length() == 0):
            continue;
        elif (cross_cube is None):
            cross_cube = p;
        elif (p is not None):
            if (p.sub_vec(ray.point).length() < cross_cube.sub_vec(ray.point).length()):
                cross_cube = p;
                
    cross_mirror_point = None;
    cross_mirror_plane = None;
    for plane in mirror:
        p = plane.cross(ray);
        if (p is not None and p.sub_vec(ray.point).length() == 0):
            continue;
        elif (cross_mirror_point is None):
            cross_mirror_point = p;
            cross_mirror_plane = plane;
        elif (p is not None):
            if (p.sub_vec(ray.point)).length() < cross_mirror_point.sub_vec(ray.point).length():
                cross_mirror_point = p;
                cross_mirror_plane = plane;
                
    if (cross_mirror_point is None or cross_cube.sub_vec(ray.point).length() < cross_mirror_point.sub_vec(ray.point).length()):
        ray.point = cross_cube;
        break;
    else:
        res = ray.rifle(cross_mirror_plane);
        if (not res):
            break;

if (ray.energy == 0):
    out.write('0\n');
    out.write(str(ray.point.x) + ' ' + str(ray.point.y) + ' ' + str(ray.point.z) + '\n');
else:
    out.write('1\n');
    out.write(str(ray.energy) + '\n');
    out.write(str(ray.point.x) + ' ' + str(ray.point.y) + ' ' + str(ray.point.z) + '\n');
    out.write(str(ray.vector.x) + ' ' + str(ray.vector.y) + ' ' + str(ray.vector.z) + '\n');

inp.close();
out.close();
