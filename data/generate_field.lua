-- generating maze and placing character on the right place

value = nil;
xPosition = 150;
yPosition = 150;

-- Put character on the map
setCharacterPosition(xPosition, yPosition - 65);

 -- Top wall
endPosition = xPosition + 400;

for i = xPosition, endPosition , 64
do
    addWallBlock("data/brickwall.jpg", i, yPosition);
    value = i;
end

xPosition = value;

endPosition = yPosition + 400;

for i = yPosition, endPosition, 64
do
    addWallBlock("data/brickwall.jpg", xPosition, i);
    value = i;
end

yPosition = value;

endPosition = xPosition + 200;

for i = xPosition, endPosition , 64
do
    addWallBlock("data/brickwall.jpg", i, yPosition);
    value = i;
end

xPosition = value;

endPosition = yPosition - 500;

for i = yPosition, endPosition, 64
do
    addWallBlock("data/brickwall.jpg", xPosition, i);
    value = i;
end

yPosition = value;
