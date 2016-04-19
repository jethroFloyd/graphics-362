x = [2, -3, -4, 3, 2];
y = [2, 4, -2, -3, 2];
z = ones(size(x));

plot(x, y, 'b*-');
axis([-10, 10, -10, 10]);
pts = [x;y;z];
display(pts)
trans = [1, 0, 2; 0, 1, 3; 0, 0, 1];
rtrans = [1, 0, -2; 0, 1, -3; 0, 0, 1];

prompt = 'Input';
in=-1;
while in ~= 0
    in = input(prompt);
    if in==1
        % scaling
        T = [2, 0, 0; 0, 1.5, 0; 0, 0, 1];
    elseif in==-1
        % rev scaling
        T = [0.5, 0, 0; 0, 2/3, 0; 0, 0, 1];
    elseif in==2
        % reflection
        T = [-1, 0, 0; 0, 1, 0; 0, 0, 1];
    elseif in==3
        % shear
        T = [1, 1, 0; 0, 1, 0; 0, 0, 1];
    elseif in==-3
        % rev shear
        T = [1, -1, 0; 0, 1, 0; 0, 0, 1];
    elseif in==4
        % rotation
        T = [cosd(45), -sind(45), 0; sind(45), cosd(45), 0; 0, 0, 1];
    elseif in==5
        % translation
        T = [1, 0, 1;0, 1, 0.5; 0, 0, 1];
     elseif in==-5
        % rev translation
        T = [1, 0, -1;0, 1, -0.5; 0, 0, 1];
    end
    pts = trans*T*rtrans*pts;
    plot(pts(1,:), pts(2,:), 'r*-');
    axis([-10, 10, -10, 10]);
    display(pts)
end 