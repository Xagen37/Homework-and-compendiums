from math import *;

def readMat(n, m, s):
    List = [];
    for i in range(n):
        row = [];
        for j in range(m):
            row.append(float(s[i * m + j]));
        List.append(row);
    return List;

def multConst(Matrix, const):
    #print(Matrix);
    const = float(const);
    for i in range(len(Matrix)):
        for j in range(len(Matrix[i])):
            Matrix[i][j] = float(Matrix[i][j]);
            Matrix[i][j] *= const;
    return Matrix;

def transpose(Matrix):
    for i in range(len(Matrix)):
        for j in range(i + 1, len(Matrix[i])):
            Matrix[i][j], Matrix[j][i] = Matrix[j][i], Matrix[i][j];
    return Matrix;

def sumMat(A, B):
    if (len(A) != len(B) or len(A) == 0):
        return [];
    else:
        for i in range (len(A)):
            if (len(A[i]) != len(B[i])):
                return [];
            else:
                for j in range(len(A[i])):
                    A[i][j] = float(A[i][j]);
                    B[i][j] = float(B[i][j]);
                    A[i][j] += B[i][j];
    return A;

def multMat(A, B):
    if (len(A) == 0 or len(B) == 0 or len(A[0]) != len(B)):
        return [];
    else:
        C = [];
        for i in range(len(A)):
            row = [];
            for j in range(len(B[0])):
                cnt = 0.0;
                for k in range(len(A[0])):
                    A[i][k] = float(A[i][k]);
                    B[k][j] = float(B[k][j]);
                    cnt += float(A[i][k] * B[k][j]);
                row.append(cnt);
            C.append(row);
        return C;

def calc(A, B, C, D, F, a, b):
    X = sumMat\
    (\
        multMat\
        (\
            multMat\
            (\
                C,\
                transpose\
                (\
                    sumMat\
                    (\
                        multConst(A, a),\
                        multConst(transpose(B), b)\
                    )\
                )\
            ),\
            D\
        ),\
        multConst(F, -1.0)\
    );
    return X;
    
        
inp = open("input.txt", "r");
out = open("output.txt", "w");

s = inp.readline();
if (s == ""):
    s = inp.readline();
s = s.split();
a = float(s[0]);
b = float(s[1]);

s = inp.readline();
if (s == ""):
    s = inp.readline();
s = s.split();
nA = int(s[0]);
mA = int(s[1]);
s = inp.readline();
if (s == ""):
    s = inp.readline();
s = s.split();
A = readMat(nA, mA, s);

s = inp.readline();
if (s == ""):
    s = inp.readline();
s = s.split();
nB = int(s[0]);
mB = int(s[1]);
s = inp.readline();
if (s == ""):
    s = inp.readline();
s = s.split();
B = readMat(nB, mB, s);

s = inp.readline();
if (s == ""):
    s = inp.readline();
s = s.split();
nC = int(s[0]);
mC = int(s[1]);
s = inp.readline();
if (s == ""):
    s = inp.readline();
s = s.split();
C = readMat(nC, mC, s);

s = inp.readline();
if (s == ""):
    s = inp.readline();
s = s.split();
nD = int(s[0]);
mD = int(s[1]);
s = inp.readline();
if (s == ""):
    s = inp.readline();
s = s.split();
D = readMat(nD, mD, s);

s = inp.readline();
if (s == ""):
    s = inp.readline();
s = s.split();
nF = int(s[0]);
mF = int(s[1]);
s = inp.readline();
if (s == ""):
    s = inp.readline();
s = s.split();
F = readMat(nF, mF, s);


X = calc(A, B, C, D, F, a, b);
if (len(X) == 0 or len(X[0]) == 0):
    out.write("0");
else:
    out.write("1\n");
    out.write(str(len(X)) + ' ' + str(len(X[0])) + '\n');
    for i in range (len(X)):
        for j in range (len(X[0])):
            out.write(str(X[i][j]) + ' ');

inp.close();
out.close();
