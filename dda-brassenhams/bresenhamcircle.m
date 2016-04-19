R = 200;

d = 1-R;
x = 0;
y = R;

arrayx = zeros(1, R);
arrayy = zeros(1, R);

k=2;
arrayx(1)=x;
arrayy(1)=y;
while x<=y
    if d<0
        d = d + (2*x) + 1;
    else
        d = d + (2*(x-y)) + 1;
        y = y - 1;
    end
    x = x+1;
    arrayx(k) = x;
    arrayy(k) = y;
    k = k + 1;
end

arrayx = arrayx(find(arrayy,1,'first'):find(arrayy,1,'last'));
arrayy = arrayy(find(arrayy,1,'first'):find(arrayy,1,'last'));

farrayx = [arrayx fliplr(arrayy) arrayy fliplr(arrayx) -arrayx -fliplr(arrayy) -arrayy -fliplr(arrayx)];
farrayy = [arrayy fliplr(arrayx) -arrayx -fliplr(arrayy) -arrayy -fliplr(arrayx) arrayx fliplr(arrayy)];

plot(farrayx, farrayy);

axis([-500, 500, -500, 500]);