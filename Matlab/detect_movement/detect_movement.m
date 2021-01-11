% Constructs a multimedia reader object
vidReader = VideoReader('echo2.avi');

% Initialize the optical flow object
% threshold for noise reduction 
%  - bigger => less movement detected
%  - smaller => more prone to noise and false detection
opticFlow = opticalFlowLK('NoiseThreshold', 0.009);

mse = [];
while hasFrame(vidReader)
    % Read the rgb frame
    frameRGB  = readFrame(vidReader);
    % Convert rgb to grayscale
    frameGray = rgb2gray(frameRGB);
    
    % Smooth with wiener2 or imdiffusefilt
    % Latter gives better results in mse
    %frameSmooth = wiener2(frameGray, [5,5]);
    frameSmooth = imdiffusefilt(frameGray);
    
    % Compute optical flow
    flow = estimateFlow(opticFlow, frameSmooth);
    % flow = estimateFlow(opticFlow, frameGray);
    
    % Display rgb video frame with flow vectors
    imshow(frameRGB);
    hold on;
    plot(flow, 'DecimationFactor', [5 5], 'ScaleFactor', 10);
    drawnow;
    hold off;
    mse = [mse, immse(frameGray, frameSmooth)];
end


% Echo2 is for MI because left ventricile wall does not pump normally
% but rather seems to be in blocked by something or plaqued