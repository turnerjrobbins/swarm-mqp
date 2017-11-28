import numpy
import openCV

#Function to transform UGV coords to global
#Takes in coordinates of UAV in global frame and coordinates of UGV in UAV camera frame
def TransformtoGlobal(UAV_pos, UGV_pos):
	
	return globalUGV
#Function to filter UAV image for two points of color, find the midpoint of the
#resultant line, and find the line orientation.
def ColorProcessing(cam_img, start_color, end_color):
	thresholded = thresholdImg(cam_img, start_color, end_color)
	UGV_camframepos = getMidpoint(thresholded)
	UGV_camframerot = getAngle(thresholded)
	UGV_campose = [UGV_camframepos, UGV_camframerot]
	return UGV_campose
#start_color and end_color are rgb values
def thresholdImg(cam_img, start_color, end_color):
#TODO: figure out how opencv works and use it for this
	return image

#finds the midpoint of a line formed by 2 points in an image - used to determine where
#the robot is in the UAV's frame of reference
def getMidpoint(image):
	centroids = getCentroids(image)
	x1 = centroids[1].x
	x2 = centroids[2].x
	y1 = centroids[1].y
	y2 = centroids[2].y
	xmid = abs(x1+x2)/2
	ymid = abs(y1+y2)/2
	xycoords = [xmid ymid]
	return xycoords
#get the centers of circles in an image and return them as xy coordinate pairs in a list
def getCentroids(image):
#TODO: Figure out how opencv works and use it for this
	return centroids
#angle of line in image; shows orientation of the robot with respect to UAV reference frame
def getAngle(image):
	#make a triangle
	centroids = getCentroids(image)
	x1 = centroids[1].x
	x2 = centroids[2].x
	y1 = centroids[1].y
	y2 = centroids[2].y
	xleg = abs(x1-x2)+x1
	yleg = abs(y1-y2)+y1
	anglerot = arctan(yleg/xleg)
	return anglerot


