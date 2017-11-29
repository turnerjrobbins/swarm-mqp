function [transformmatrix] = transform(uavpos)
    xuav = uavpos(1);
    yuav = uavpos(2);
    zuav = uavpos(3);
    xang = uavpos(4);
    yang = uavpos(5);
    zang = uavpos(6);
    xrotate = [1,0,0;
        0,cos(xang),-sin(xang);
        0,sin(xang),cos(xang)];
    yrotate = [cos(yang),0,sin(yang);
        0,1,0;
        -sin(yang),0,cos(yang)];
    zrotate = [cos(zang), -sin(zang), 0;
        sin(zang), cos(zang),0;
        0,0,1];
    rotatrix = xrotate*yrotate*zrotate;
    translatrix = [xuav;yuav;zuav;1];
    transformmatrix = [rotatrix(1,1),rotatrix(1,2),rotatrix(1,3),translatrix(1);
                       rotatrix(2,1),rotatrix(2,2),rotatrix(2,3),translatrix(2);
                       rotatrix(3,1),rotatrix(3,2),rotatrix(3,3),translatrix(3);
                       0,0,0,1];
   end

