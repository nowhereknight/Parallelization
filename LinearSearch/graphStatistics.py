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
plt.title("Comparación de Tiempos de Ejecución en Busqueda Lineal")
plt.plot(x,y,label="Serial runtime")
plt.plot(x,z, color="red",label="Parallel runtime")
plt.legend(loc="upper left")
plt.ylabel('Runtime [sec]')
plt.axis((0,sizes[-1],0,0.005))
plt.show()
fig.savefig('statistics.png')
