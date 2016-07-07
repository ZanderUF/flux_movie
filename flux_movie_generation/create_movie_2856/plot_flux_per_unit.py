#-- Read array from KENO and have corespond to x,y axis 
#-- for plotting fluxes
#-- reads in array of units and file containing units and total flux
#---------------------Declarations---------------------------
import matplotlib.cm as cm
import matplotlib as mpl
import numpy as np
import matplotlib.pyplot as plt
#---------------------Variables------------------------------
i=0
j=0
k=0
array_x_y_unit = []
x_pts =   []
y_pts =   []
z_pts =   []
color_z = []
#---------------GET THE UNIT NUMBERS FROM KENO ARRAY----------
filename= raw_input("Enter the file name containing the array: ")
file_tot_flux = raw_input("Enter file containing total flux: ")

#-------------------Read in total----------------------------
data = np.loadtxt(filename)
data_tot_flux = np.loadtxt(file_tot_flux)
unit_from_tot = data_tot_flux[:,0]
tot_flux_val = data_tot_flux[:,1]
max_x=len(data)
max_y=len(data[0])

#--------------------Define Object--------------------------
class point_on_grid(object):
	def __init__(self,x,y,unit_num,tot_flux):
		self.x=x
		self.y=y
		self.unit_num=unit_num
		self.tot_flux=tot_flux

#-------------------------------------------------------------

for i in range(max_x):
	for j in range(max_y):
		for k in range(len(data_tot_flux)):
			if data[i][j] == unit_from_tot[k]:
				tot_flux=tot_flux_val[k]
		point = point_on_grid(i,j,data[i][j],tot_flux)
		
		array_x_y_unit.append(point)
		j+=1
	i+=1
for q in range (len(array_x_y_unit)):
	x_pts.append(array_x_y_unit[q].x)
	y_pts.append(array_x_y_unit[q].y)
	z_pts.append(round(array_x_y_unit[q].tot_flux,6))

zlog = np.log(z_pts)
i=0
for i in range(len(zlog)):
	 round(zlog[i],4)

plt.colorbar(zlog)
#-------------------------------------------------------------
mymap = mpl.colors.LinearSegmentedColormap.from_list('mycolors',['blue','red'])
Z = [[0,0],[0,0]]
levels = range(min,max+step,step)
CS3 = plt.contourf(Z, levels, cmap=mymap)
plt.clf()

plt.colorbar(CS3) # using the colorbar info I got from contourf

#-------------PLOT-------------------------------------------
plt.scatter(x_pts,y_pts,marker='s',s=250,c=zlog)

figname = file_tot_flux + "image"
plt.savefig(figname + '.pdf')
#plt.show()
