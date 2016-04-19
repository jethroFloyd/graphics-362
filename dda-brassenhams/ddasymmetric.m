x1 = 100;
y1 = 200;
x2 = 500;
y2 = 500;

dx = x2-x1;
dy = y2-y1;

while dx>1 || dy>1
    dy = dy/2;
    dx = dx/2;
end

x = round(x1:dx:x2);
y = round(y1:dy:y2);

plot(x, y);

axis([0, 1000, 0, 1000]);





