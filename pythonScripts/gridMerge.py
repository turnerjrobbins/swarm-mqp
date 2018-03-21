#Created by Mathew Schwartzman on 27 November 2017

import numpy as np
import math

from scipy import misc
import matplotlib.pyplot as plt

rows = 20
cols = 20

#########-------TEST ARRAYS------#######
a = np.array([[1,0,0,0,0],
			  [0,0,0,0,0],
			  [0,0,0,1,0],
			  [0,0,1,2,1],
			  [0,0,0,1,0]])

b = np.array([[0,0,0,0,0],
			  [0,0,1,0,0],
			  [0,1,2,1,0],
			  [0,0,1,0,0],
			  [0,0,0,0,0]])

c = np.array([[0,0,0,0,0],
			  [0,0,1,0,0],
			  [0,1,2,3,0],
			  [0,0,1,0,0],
			  [0,0,0,0,0]])

d = np.array([[0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]])

e = np.array([[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
			  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]])

class Transformation:

	def __init__(self, stillArray, transArray):
		self.stillArray = stillArray
		self.transArray = transArray
		self.delta = simpleDelta(stillArray,transArray)

def createTransList(still, shake, radius):
	simplelist = []
	x = int(cols/2)
	y = int(rows/2)
	for m in range(x - radius, x + radius + 1):
		for n in range(y - radius, y + radius + 1):
			lat = m-x
			lon = n-y
			#print lat
			#print lon
			shook = generalTranslateX(lat, shake)
			shooken = generalTranslateY(lon, shook)
			#print(shooken)
			transformation = Transformation(still,shooken)
			simplelist.append(transformation)
	#print len(simplelist)
	return simplelist

def createRotList(still, shimmy, tilt):
	simplelist = []
	x = int(cols/2)
	y = int(rows/2)

	orig = Transformation(still, shimmy)
	simplelist.append(orig)

	for m in range(tilt):
		shimmied = rotateCCW(tilt*10, shimmy, x, y)
		transformation = Transformation(still, shimmied)
		simplelist.append(transformation)

	for m in range(tilt):
		shimmied = rotateCW(tilt*10, shimmy, x, y)
		transformation = Transformation(still, shimmied)
		simplelist.append(transformation)
	print len(simplelist)
	return simplelist

def simpleDelta(matrix1, matrix2):	#simple similarity function that returns the absolute scalar differences between cell values
	deltaMatrix = matrix1 - matrix2
	deltaScalar = 0
	for el in deltaMatrix.flatten():
		deltaScalar = deltaScalar + abs(el)
	return deltaScalar

def translateUpOne(array):
	new= np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	array_flat = array.flatten()	#flatten the input array
	for el in range(cols, (rows*cols)):	#start on second row
		np.put(new, el-cols, array_flat[el])	#put all the elements up in the new array d
	return new

def translateUp(distance, target_array):	#distance is given in cells
	new = np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	array_flat = target_array.flatten()	#flatten the input array
	for el in range(cols*distance, (rows*cols)):	#start on second row
		np.put(new, el-cols*distance, array_flat[el])	#put all the elements up in the new array d
	return new

def translateDown(distance, target_array):	#distance is given in cells
	target_array = np.rot90(target_array)
	target_array = np.rot90(target_array)
	new = np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	array_flat = target_array.flatten()	#flatten the input array
	for el in range(cols*distance, (rows*cols)):	#start on second row
		np.put(new, el-cols*distance, array_flat[el])	#put all the elements up in the new array d
	new = np.rot90(new)
	new = np.rot90(new)
	return new

def generalTranslateY(distance, target_array):
	if distance < 0:
		new = translateUp(abs(distance),target_array)
	else:
		new = translateDown(abs(distance),target_array)
	return  new

def translateRight(distance, target_array):
	new= np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	target_array = np.rot90(target_array)
	array_flat = target_array.flatten()	#flatten the input array
	for el in range(cols*distance, (rows*cols)):	#start on second row
		np.put(new, el-cols*distance, array_flat[el])	#put all the elements up in the new array d
		#print el
	new = np.rot90(new)
	new = np.rot90(new)
	new = np.rot90(new)
	return new

def translateLeft(distance, target_array):
	new = np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	target_array = np.rot90(target_array)
	target_array = np.rot90(target_array)
	target_array = np.rot90(target_array)
	array_flat = target_array.flatten()	#flatten the input array
	for el in range(cols*distance, (rows*cols)):	#start on second row
		np.put(new, el-cols*distance, array_flat[el])	#put all the elements up in the new array d
	new = np.rot90(new)
	return new

def generalTranslateX(distance, target_array):
	if(distance < 0):
		new = translateLeft(abs(distance), target_array)
	else:
		new = translateRight(abs(distance), target_array)
	return new

def rotateCCW(angle, target_array, centerx, centery):	#use increments of 10 degrees
	new = np.zeros(rows*cols).reshape(rows, cols)
	if(angle>90):
		for n in range(int(angle/90)):
			target_array = np.rot90(target_array)
		angle = angle - 90*int(angle/90)
	angle = angle*-1
	for row in range(rows):
		for col in range(cols):
			newx = np.cos(math.radians(angle))*(col-centerx)-np.sin(math.radians(angle))*(row-centery)+centerx#col	
			newy = np.sin(math.radians(angle))*(col-centerx)+np.cos(math.radians(angle))*(row-centery)+centery#row
			roundedx = int(round(newx))
			roundedy = int(round(newy))
			# print angle
			# print rows
			# print cols
			# print "newstuff"
			# print newx
			# print newy
			# print "rounded"
			# print roundedx
			# print roundedy
			if((0 <= roundedy < rows-1) and (0 <= roundedx < cols-1)):				
				new[int(round(newy)),int(round(newx))] = target_array[row,col]	#add check to see if in matrix
	return new

def rotateCW(angle, target_array, centerx, centery):	#use increments of 10 degrees
	new = np.zeros(rows*cols).reshape(rows, cols)
	if(angle>90):
		for n in range(int(angle/90)):
			target_array = np.rot90(target_array)
		angle = angle - 90*int(angle/90)
	angle = angle*1
	for row in range(rows):
		for col in range(cols):
			newx = np.cos(math.radians(angle))*(col-centerx)-np.sin(math.radians(angle))*(row-centery)+centerx#col	
			newy = np.sin(math.radians(angle))*(col-centerx)+np.cos(math.radians(angle))*(row-centery)+centery#row
			roundedx = int(round(newx))
			roundedy = int(round(newy))
			if((0 <= roundedy < rows-1) and (0 <= roundedx < cols-1)):				
				new[int(round(newy)),int(round(newx))] = target_array[row,col]	#add check to see if in matrix
	return new

def findOptTranslation(listoftranslations):
	optimized_list = sorted(listoftranslations, key = lambda transformation: transformation.delta)
	best = optimized_list[0]
	#print best.delta
	#print "best array"
	#print best.transArray
	return best

def findOptRotation(listofrotations):
	optimized_list = sorted(listofrotations, key = lambda transformation: transformation.delta)
	best = optimized_list[0]
	#print best.delta
	#print "best array"
	#print best.transArray
	return best

def shimmyShake(matrix1, matrix2, sensitivity):

	radius = 6#sensitivity * cols/2
	listoftranslations = createTransList(matrix1, matrix2, radius)
	transResult = findOptTranslation(listoftranslations)

	tilt = 9#sensitivity * 36
	listofrotations = createRotList(matrix1, transResult.transArray, tilt)
	finalResult = findOptRotation(listofrotations)
	return transResult

def shake(matrix1, matrix2, sensitivity):
	radius = 21
	listoftranslations = createTransList(matrix1, matrix2, radius)
	result = findOptRotation(listoftranslations)

	return result

def shimmy(matrix1, matrix2, sensitivity):
	tilt = 4
	listoftransformations = createRotList(matrix1, matrix2, tilt)
	result = findOptRotation(listoftransformations)

	for obj in listoftransformations:
		#plt.figure(figsize=(6,3.2))
		#plt.imshow(obj.transArray)
		print obj.delta

	return result

def actuator(fixed, flux, targDelta):
	var = flux
	#while(simpleDelta(fixed, var) > targDelta):

	# print simpleDelta(fixed, var)
	# var = shake(fixed, var, 1).transArray
	print simpleDelta(fixed, var)
	var = shimmy(fixed, var, 2).transArray
	# print simpleDelta(fixed, var)
	# var = shake(fixed, var, 1).transArray
	
	print simpleDelta(fixed, var)
	return var

f = generalTranslateY(6,(rotateCW(45, e, 10,10)))
g = rotateCCW(20, e, 10, 10)

stationary = d
original = f #rotateCCW(10, generalTranslateY(6,generalTranslateX(6,e)),10,10)
transformed = actuator(stationary, original, 12)

plt.figure(figsize=(6,3.2))
plt.imshow(d)
plt.figure(figsize=(6,3.2))
plt.imshow(original)
plt.figure(figsize=(6,3.2))
plt.imshow(transformed)
plt.colorbar(orientation='vertical')
plt.show()