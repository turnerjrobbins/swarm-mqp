#Function to update transform frame after robot global position changes
#Takes in coordinates of UAV in global frame and coordinates of UGV in UAV camera frame
def UpdateTransforms(UAV_pos, UGV_pos):


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

def getMidpoint(image):

	return xyzcoords

def getAngle(image):

	return anglerot


