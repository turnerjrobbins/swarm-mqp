function [angle,midpt] = findrobot(imgpath)
readimg = imread(imgpath);
%threshed = threshold(readimg);
greyed = rgb2gray(readimg);
[centers, radii] = imfindcircles(greyed, 80, 'Sensitivity', 1);
x1 = centers(1,1);
x2 = centers(2,1);
y1 = centers(1,2);
y2 = centers(2,2);
angle = atan(abs(y1-y2)/abs(x1-x2));
midpt = [((x1-x2)/2)+x2, ((y1-y2)/2)+y2];
imshow(readimg);
v = viscircles(centers,radii);
v2 = viscircles(midpt, 2);
end

