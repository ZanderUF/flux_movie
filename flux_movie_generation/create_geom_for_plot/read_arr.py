#---- Read array from KENO and have corespond to x,y axis for plotting

#!!---Declarations---!
import matplotlib.cm as cm
import matplotlib as mpl
import numpy as np
import matplotlib.pyplot as plt
#----Variables---!
array_x_y_unit = []
x_pts = []
y_pts = []
z_pts = []
color_z = []
filename= raw_input("Enter the file name containing the array: ")

data = np.loadtxt(filename)

class point_on_grid(object):
	def __init__(self,x,y,unit_num,color):
		self.x=x
		self.y=y
		self.unit_num=unit_num
		self.color=color
#----
max_x=len(data)
max_y=len(data[0])
i=0
j=0
color = 'blue'
for i in range(max_x):
	for j in range(max_y):
		point = point_on_grid(i,j,data[i][j],'red')
		array_x_y_unit.append(point)
		j+=1
	i+=1
for q in range (len(array_x_y_unit)):
	x_pts.append(array_x_y_unit[q].x)
	y_pts.append(array_x_y_unit[q].y)
	z_pts.append(array_x_y_unit[q].unit_num)

#color = [str(item/255.) for item in z_norm]

plt.scatter(x_pts,y_pts,marker='s',s=150,c=z_pts)

plt.show()
