function circle = drawCircle()
sides = 12000;
angle = 2*pi/sides;
angle_in_degree = 0:angle:360-angle;
radius=ones(1, numel(angle_in_degree));
polar(angle_in_degree,radius);
end