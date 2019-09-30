import matplotlib.pyplot as plt
import numpy as np
def getRegistries():
	sizes=[]
	serial=[]
	parallel=[]
	with open("statistics.txt") as file:
		for line in file:
			size, par, normal,line=line.split("::")
			sizes.append(int(size))
			serial.append(float(normal))
			parallel.append(float(par))

	return sizes,serial, parallel

sizes,serials, parallels=getRegistries()

x=np.array(sizes)
y=np.array(serials)

z=np.array(parallels)
fig=plt.figure(figsize=(10,8),dpi=80)
plt.plot(x,y)
plt.plot(x,z, color="red")
plt.ylabel('Runtime [sec]')
plt.show()
fig.savefig('statistics.png')
