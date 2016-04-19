x1 = 100;
y1 = 200;
x2 = 500;
y2 = 500;

dx = x2-x1;
dy = y2-y1;

d = 2*dy-dx;
dE = 2*dy;
dNE = 2*(dy-dx);

x = x1;
y = y1;

arrayx = zeros(1, dx);
arrayy = zeros(1, dx);

k=2;
arrayx(1)=x;
arrayy(1)=y;
while x<x2 && y<y2
    if d<0
        d = d + dE;
    else
        d = d + dNE;
        y = y + 1;
    end
    x = x+1;
    arrayx(k) = x;
    arrayy(k) = y;
    k = k + 1;
end

plot(arrayx, arrayy);

axis([0, 1000, 0, 1000]);