%% measure.m
% Image processing to measure the length of a finger using a template
clear
clc

totalLengthInches = 6;
% Read Image
image = imread("hand3.jpeg");

original = image;

% Image processing 
[len,wid] = size(image);
image = rgb2gray(image);
image = imrotate(image,-90);

%Find Reference points
refPoints = detectSURFFeatures(image,'ROI',[1 1 (size(image,1)/4) (size(image,2)/2)]);
refPoints2 = detectSURFFeatures(image,'ROI',[refPoints.selectStrongest(1).Location(1,1)+5 refPoints.selectStrongest(1).Location(1,2)+5 (size(image,1)/4) (size(image,2)/4)]);


points = detectSURFFeatures(image,'ROI',[(size(image,1)/4) (size(image,2)/4) (size(image,1)/4) (size(image,2)/2)]);

% Show the image
imshow(image); hold on;
plot(refPoints2.selectStrongest(10));
plot(points.selectStrongest(2));
least = 1000000000;
% Find the most relevant reference points
for i = 1:10
    x = refPoints2.selectStrongest(10).Location(i,1);
    y = refPoints2.selectStrongest(10).Location(i,2);
    
    if (x + y) < least 
        least = x + y;
        leastX = x;
        leastY = y;
        leastIndex = i;
    end
    
end

for i = 1:10
    if refPoints2.selectStrongest(10).Location(i,2) > (leastY+100) && refPoints2.selectStrongest(10).Location(i,1) < (leastX + 50)
        bottomIndex = i;
    end
end
% Display reference points
disp(refPoints2.selectStrongest(10).Location(bottomIndex,1))
disp(refPoints2.selectStrongest(10).Location(bottomIndex,2))


disp(points.selectStrongest(2).Location(1,1));
disp(points.selectStrongest(2).Location(1,2));
disp(points.selectStrongest(2).Location(2,1));
disp(points.selectStrongest(2).Location(2,2));

% Calculate distance between pixels, convert to inches

dist = sqrt((points.selectStrongest(2).Location(1,1)-points.selectStrongest(2).Location(2,1))^2 + (points.selectStrongest(2).Location(1,2) - points.selectStrongest(2).Location(2,2))^2);
totalLengthPixels = sqrt((refPoints2.selectStrongest(10).Location(leastIndex,1)-refPoints.selectStrongest(10).Location(bottomIndex,1))^2 + (refPoints2.selectStrongest(10).Location(leastIndex,2) - refPoints2.selectStrongest(10).Location(bottomIndex,2))^2);
disp(dist);
P2IRatio = 1/totalLengthPixels;
fingerLengthPixels = (totalLengthPixels*6) - dist;
fingerLengthInches = fingerLengthPixels * P2IRatio;
disp(["The length of the finger is ",num2str(fingerLengthInches),"Inches"]);

