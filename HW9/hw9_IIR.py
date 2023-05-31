import matplotlib.pyplot as plt # for plotting
import numpy as np # for sine function
import csv

def avg(list):
    return sum(list)/len(list)

t = []
v=[]

with open('sigD.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        v.append(float(row[1])) # second column
        # data2.append(float(row[2])) # third column

dt = t[1]-t[0]
print(str(dt))

##### FFT The Raw Data ########
Fs = 10000                      # sample rate
Ts = 1.0/Fs;                    # sampling interval
ts = np.arange(0,t[-1],Ts)      # time vector
y = v                           # the data to make the fft from
n = len(y)                      # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T                       # two sides frequency range
frq = frq[range(int(n/2))]      # one side frequency range
Y = np.fft.fft(y)/n             # fft computing and normalization
Y = Y[range(int(n/2))]


##### Filter the Data ########
f = []
A = 0.9
B = 0.1

for vp in v:
    if len(f)==0:
        f.append(0)
    else: 
        f.append(f[-1]*A+vp*B)


##### FFT The Filtered Data ########
Fs = 10000                      # sample rate
Ts = 1.0/Fs;                    # sampling interval
ts = np.arange(0,t[-1],Ts)      # time vector
y = f                           # the data to make the fft from
n = len(y)                      # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T                       # two sides frequency range
frq = frq[range(int(n/2))]      # one side frequency range
Z = np.fft.fft(y)/n             # fft computing and normalization
Z = Z[range(int(n/2))]



##### Plot All The Data ########
fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t,v,'b')
ax1.plot(t,f,'r')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'b') # plotting the fft
ax2.loglog(frq,abs(Z),'r')
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()