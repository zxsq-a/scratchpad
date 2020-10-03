import sys
import numpy as np
from scipy.integrate import odeint
import svgwrite
import math

#pendulum lengths, meters
L1, L2 = 1, 1
#masses, kilos
m1, m2 = 0.5, 0.5
#gravity, m/s2
g = 9.81
#create output svg
svgPath = svgwrite.Drawing('/Users/user/Desktop/pendulum.svg', profile='tiny')
#svg pathing storage vars
xprev, yprev = 0,0
loopcount = 0

def deriv(y,t,L1,L2,m1,m2):
    #first derivative of y=theta1, z1, theta2, z2
    theta1, z1, theta2, z2 = y
    
    cost, sint = np.cos(theta1-theta2), np.sin(theta1 - theta2)
    
    theta1prime = z1
    z1pa = m2 * g * np.sin(theta2) * cost
    z1pb = m2 * sint * (L1 * pow(z1, 2) * 2 * cost + L2 * pow(z2, 2))
    z1pc = (m1 + m2) * g * np.sin(theta1)
    z1pd = (m1 + m2 * pow(sint, 2))
    z1prime = ((z1pa - z1pb) - z1pc) / L1 / z1pd
    
    theta2prime = z2
    z2pa = ((m1 + m2) * (L1 * pow(z2, 2) * sint - g * np.sin(theta2) + g * np.sin(theta1) * cost)) 
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

tmax, dt = 3000, 0.01 #how long it runs, how long between steps (quantization)
t = np.arange(0, (tmax + dt), dt)
#initial conds
y0 = np.array([3 * np.pi / 7, 0, 3 * np.pi / 4, 0])

#do integration
y = odeint(deriv, y0, t, args=(L1, L2, m1, m2))

#sancheck total energy
EDRIFT = 0.05
E = calcNRG(y0)
#sys.exit('EDRiFT of: {} oob, >0.05'.format(EDRIFT)) if np.max(np.sum(np.abs(calcNRG(y) - E))) > EDRIFT else sys.exit('complete')

# Unpack z and theta as a function of time
theta1, theta2 = y[:,0], y[:,2]

# Convert to Cartesian coordinates of the two bob positions.
x1 = L1 * np.sin(theta1)
y1 = -L1 * np.cos(theta1)
x2 = x1 + L2 * np.sin(theta2)
y2 = y1 - L2 * np.cos(theta2)

#add segment to svg
def svgAdd(xa, xb, ya, yb, svgName):
    global loopcount
    #xa,ya are inner pendulum, xb,yb are outer
    if (loopcount == 0):
        svgwrite.shapes.Circle(center=(xb,yb), r='1px')
        xprev = xb
        yprev = yb
        loopcount+=1
    else:
        svgwrite.shapes.Line(start=(xprev,yprev), end=(xb,yb))
        xprev = xb
        yprev = yb
        loopcount+=1
        
    return 0
#svgAdd(x1, y1, x2, y2, svgPath)
#svgPath.save()

precision=10
di=(1/precision/dt)
cast_size=int(math.floor(t.size))
cast_di=int(math.floor(di))
for i in range (0, cast_size, cast_di):
    print(str(i//di)+'/'+str(t.size//di))
    svgAdd(x1, y1, x2, y2, svgPath)
    
svgPath.save()
