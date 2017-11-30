function [angle,midpt] = findrobot(imgpath)
readimg = imread(imgpath);
threshedred = createMask(readimg, 1);
threshedyellow = createMask(readimg,2);
[centerred, radiusred] = imfindcircles(threshedred, 85, 'Sensitivity',1);
[centeryel, radiusyel] = imfindcircles(threshedyellow, 85, 'Sensitivity',1);
x1 = centerred(1,1);
x2 = centeryel(1,1);
y1 = centerred(1,2);
y2 = centeryel(1,2);
angle = atan(abs(y1-y2)/abs(x1-x2));
midpt = [((x1-x2)/2)+x2, ((y1-y2)/2)+y2];
rgb = insertShape(readimg,'Line', [x1,y1,x2,y2], 'Color', 'blue', 'LineWidth', 8);
imshow(rgb);
v = viscircles([centerred(1,1),centerred(1,2);centeryel(1,1),centeryel(1,2)], [radiusred(1);radiusyel(1)]);
end

