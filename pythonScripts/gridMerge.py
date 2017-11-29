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
			  [0,1,2,999,0],
			  [0,0,1,0,0],
			  [0,0,0,0,0]])

d = np.array([[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
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
	
	#array attribute

	#delta attribute

	def __init__(self, transformedArray, delta):
		self.transformedArray = realpart
		self.delta = delta
	


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

def translateDown(distance, target_array):
	new= np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	array_flat = target_array.flatten()	#flatten the input array
	for el in range((rows*cols - cols), -1, -1):
		np.put(new, (el+cols*distance)-1, array_flat[el-1])
		#print el
	return new

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
		#print el
	new = np.rot90(new)
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

#print a
#print b
#print c
#print simpleDelta(translateLeft(1, translateUp(1,a)),b)
# print translateUp(1, c)
# print translateDown(1, c)
# print translateRight(1, c)
# print translateLeft(1, c)
#print rotateCCW(200,c,2,2)
print "break"
print rotateCW(20,d,10,10)