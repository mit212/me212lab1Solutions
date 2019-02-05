#!/usr/bin/python

# 2.12 Lab 1 Realtime controller plot
# Peter Yu Sept 2016

import serial
import syslog
import time
import numpy as np
import matplotlib.pyplot as plt
import traceback
import matplotlib.animation as animation

port = '/dev/ttyACM0'

timeWindow = 5;         # Seconds
serialFrequency = 100;  # Hz. Setting in Arduino
windowWidth = timeWindow * serialFrequency;

ard = serial.Serial(port, 115200, timeout=5)

i = 0

valbuf = [0] * windowWidth
timebuf = []

time.sleep(1) # let arduino reset
fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

actualY = [0] * windowWidth;
desiredY = [0] * windowWidth;
commandY = [0] * windowWidth;
timeX = np.linspace(-timeWindow, 0, windowWidth).tolist();

p = ax1.plot(timeX, actualY, timeX, desiredY, timeX, commandY);
plt.title('2.12 Lab 1: Wheel Velocity Control');
plt.xlabel('Time (second)');
plt.ylabel('Wheel Velocity (m/s)');
plt.legend(p, ['Actual', 'Desired', 'Command/1000'], loc=2,
           ncol=3, mode="expand", borderaxespad=0.)

ard.flush()

#Read and discard starting messages
bytesToRead = ard.inWaiting()
serialDatas = ard.read(bytesToRead)

def update(frameNum, ax1):
    # Serial read section
    bytesToRead = ard.inWaiting()
    serialDatas = ard.read(bytesToRead)
    
    #serialData = ard.readline()
    for serialData in serialDatas.split('\n'):
        try:
            print "Message from arduino: ", serialData
            
            splitData = serialData.split(',')

            if len(splitData) < 6 or splitData[0] != '#':
                raise Exception("")
            newTime = float(splitData[1]) / 1000.0
            newActual = float(splitData[2])
            newDesired = float(splitData[3])
            newCommand = float(splitData[4]) / 1000.0
            
            timeX.pop(0)
            actualY.pop(0)
            desiredY.pop(0)
            commandY.pop(0)
            
            timeX.append(newTime)
            actualY.append(newActual)
            desiredY.append(newDesired)
            commandY.append(newCommand)
        except:
            #traceback.print_exc()
            print 'Bad Serial Data:', serialData
        
    p[0].set_xdata(timeX)
    p[0].set_ydata(actualY)
    p[1].set_xdata(timeX)
    p[1].set_ydata(desiredY)
    p[2].set_xdata(timeX)
    p[2].set_ydata(commandY)
    ax1.set_xlim([timeX[0], timeX[-1]])
    ax1.set_ylim([min(actualY+desiredY+[0])*1.2, max(actualY+desiredY+[0])*1.2])
    return ax1,
    
anim = animation.FuncAnimation(fig, update, 
                             fargs=(ax1,), 
                             interval=1000/serialFrequency)
# show plot
try:
    plt.show()
except:
    print 'Exit'
ard.flush()
ard.close()
