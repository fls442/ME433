from ulab import numpy as np # to get access to ulab numpy functions
import time


dt = 1/1024
t = np.arange(0.0, 1.0, dt) # 10s
# a constant plus 100Hz and 1000Hz
s1 = 4.0  *  np.sin(2 * np.pi * 100 * t)  
s2 = 0.25 *  np.sin(2 * np.pi * 1000 * t)
s3 = 2.0  *  np.sin(4 * np.pi * 50 * t)  


adds = s1 + s2 + s3

fft = np.fft.fft(adds)
length = len(adds)

for j in range(0,length-2):
    print((adds[j], adds[j+1], adds[j+2]))
    time.sleep(0.05)
    time.sleep(0.05)
