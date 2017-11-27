#Function to update transform frame after robot global position changes
#Takes in coordinates of UAV in global frame and coordinates of UGV in UAV camera frame
def TransformtoGlobal(UAV_pos, UGV_pos):


#Function to filter UAV image for two points of color, find the midpoint of the
#resultant line, and find the line orientation.
def ColorProcessing(cam_img, start_color, end_color):
	thresholded = thresholdImg(cam_img, start_color, end_color)
	UGV_camframepos = getMidpoint(thresholded)
	UGV_camframerot = getAngle(thresholded)
	UGV_campose = [UGV_camframepos, UGV_camframerot]
	return UGV_campose

def thresholdImg(cam_img, start_color, end_color):
	
	return thresholded
#finds the midpoint of a line formed by 2 points in an image - used to determine where the robot is in the UAV's frame of reference
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

def getCentroids(image):

	return centroids
#angle of line in image; shows orientation of the robot with respect to UAV reference frame
def getAngle(image):

	return anglerot


