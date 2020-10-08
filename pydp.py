import sys
import numpy as np
from scipy.integrate import odeint
import svgwrite
import math

#pendulum lengths, meters
L1, L2 = 10, 12
#masses, kilos
m1, m2 = 1, 1
#gravity, m/s2
g = 9.81
#create output svg
dwg = svgwrite.Drawing('/Users/user/Desktop/pendulum2.svg', profile='tiny', size=(25,25))
paths = dwg.add(dwg.g(id='paths'))
#svg pathing storage vars
xprev, yprev = 0,0
loopcount = 0

def deriv(y,t,L1,L2,m1,m2):
    #first derivative of y=theta1, z1, theta2, z2
    theta1d, z1, theta2d, z2 = y
    
    cost, sint = np.cos(theta1d-theta2d), np.sin(theta1d - theta2d)
    
    theta1prime = z1
    z1pa = m2 * g * np.sin(theta2d) * cost
    z1pb = m2 * sint * (L1 * pow(z1, 2) * 2 * cost + L2 * pow(z2, 2))
    z1pc = (m1 + m2) * g * np.sin(theta1d)
    z1pd = (m1 + m2 * pow(sint, 2))
    z1prime = ((z1pa - z1pb) - z1pc) / L1 / z1pd
    
    theta2prime = z2
    z2pa = ((m1 + m2) * (L1 * pow(z2, 2) * sint - g * np.sin(theta2d) + g * np.sin(theta1d) * cost)) 
    z2pb = m2 * L2 * pow(z2, 2) * sint * cost
    z2pc = (m1 + m2 * pow(sint, 2))
    z2prime = (z2pa + z2pb) / L2 / z2pc
    
    return theta1prime, z1prime, theta2prime, z2prime

def calcNRG(y):
    #total energy of system
    th1, th1d, th2, th2d = y.T
    V = -1 * (m1 + m2) * L1 * g * np.cos(th1) - m2 * L2 * g * np.cos(th2)
    Ta = (pow((L1 * th1d), 2) + pow((L2 * th2d), 2) + 2 * L1 * L2 * th1d * th2d * np.cos((th1-th2)))
    T = 0.5 * m1 * pow((L1 * th1d), 2) + 0.5 * m2 * Ta
    return T + V

# Maximum time, time point spacings and the time grid (all in s).
tmax, dt = 300, 0.001
t = np.arange(0, tmax+dt, dt)
# Initial conditions: theta1, dtheta1/dt, theta2, dtheta2/dt.
y0 = np.array([3*np.pi/7, 0, 3*np.pi/4, 0])

#do integration
y = odeint(deriv, y0, t, args=(L1, L2, m1, m2))

#sancheck total energy
EDRIFT = 0.05
E = calcNRG(y0)
#if np.max(np.sum(np.abs(calcNRG(y) - E))) > EDRIFT:
    #sys.exit('Maximum energy drift of {} exceeded.'.format(EDRIFT))
    
# Unpack z and theta as a function of time
theta1, theta2 = y[:,0], y[:,2]

# Convert to Cartesian coordinates of the two bob positions.
x1 = L1 * np.sin(theta1)
y1 = L1 * np.cos(theta1)
x2 = x1 + L2 * np.sin(theta2)
y2 = y1 - L2 * np.cos(theta2)

#add segment to svg
def svgAdd(xa, xb, ya, yb, svgName, loopno):
    global loopcount
    global xprev
    global yprev
    global paths
    l_loopno = int(loopno)
    #xa,ya are inner pendulum, xb,yb are outer
    if (loopcount == 0):
        svgwrite.shapes.Circle(center=(xb,yb), r='1px')
        xprev = xb
        yprev = yb
        loopcount+=1
    else:
        xend = xb#[l_loopno]
        yend = yb#[l_loopno]
        lines = dwg.line(start=(xprev,yprev), end=(xend, yend), stroke='black')
        paths.add(lines)
        xprev = xend
        yprev = yend
        loopcount+=1
        
    return 0
#svgAdd(x1, y1, x2, y2, dwg)
#dwg.save()

precision=10
di=(1/precision/dt)
cast_size=int(math.floor(t.size))
cast_di=int(math.floor(di))
for i in range (0, cast_size, cast_di):
    #print(str(i//di)+'/'+str(t.size//di))
    svgAdd(x1[i], y1[i], x2[i], y2[i], dwg, i)

    print("x1: ", end='')
    print(x1[i])#, end='')
    print(" y1: ", end='')
    print(y1[i], end='')
    print(" x2: ", end='')
    print(x2[i], end='')
    print(" y2: ", end='')
    print(y2[i])
    
dwg.save()
