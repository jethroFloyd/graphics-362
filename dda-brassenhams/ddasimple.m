x1 = 100;
y1 = 200;
x2 = 500;
y2 = 500;

dx = x2-x1;
dy = y2-y1;

if dx > dy
    step = dx;
else
    step = dy;
end

incx = dx/step;
incy = dy/step;

x = round(x1:incx:x2);
y = round(y1:incy:y2);

plot(x, y);

axis([0, 1000, 0, 1000]);