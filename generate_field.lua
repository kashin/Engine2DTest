-- generating maze

value = nil;
xPosition = 100;
yPosition = 100;
 -- Top wall
endPosition = xPosition + 400
for i = xPosition, endPosition , 64
do
    addWallBlock("brickwall.jpg", i, yPosition);
    value = i;
end

xPosition = value;

endPosition = yPosition + 400

for i = yPosition, endPosition, 64
do
    addWallBlock("brickwall.jpg", xPosition, i);
    value = i;
end

yPosition = value

endPosition = xPosition + 200

for i = xPosition, endPosition , 64
do
    addWallBlock("brickwall.jpg", i, yPosition);
    value = i;
end

xPosition = value;

endPosition = yPosition - 500

for i = yPosition, endPosition, 64
do
    addWallBlock("brickwall.jpg", xPosition, i);
    value = i;
end

yPosition = value
