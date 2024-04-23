%% fracDelayFBCF.m
% Zachary Miller
% 19 April 2024

clear; clc; close all;

% Impulse response
Fs = 48000; Ts = 1/Fs;
x = [1;zeros(Fs,1)];
N = length(x);

tau = 2*pi;

depth = 2; % LFO depth
speed = 2; % LFO speed (Hz)
delay = 10; % delay (samples)

g = 0.9; % feedback gain

currentAngle = 0;
angleChange = speed * Ts * tau;

index = 1;
MAX_BUFFER_SIZE = 96000;

delayBuffer = zeros(MAX_BUFFER_SIZE,1); out = zeros(N,1); y = 0;
for n=1:N

    % Feedback comb filter delay
    fbVar = x(n,1) + (-g) * y; % fbVar is arbitrary delay variable
                               % for feedback diff eq calculation

    % Fractional delay
    lfo = depth * sin(currentAngle);
    
    currentAngle = currentAngle + angleChange;
    if (currentAngle > tau)
        currentAngle = currentAngle - tau;
    end
    
    % Delay buffer
    % "delay" can be fraction
    
    d1 = floor(delay+lfo);
    d2 = d1 + 1;
    g2 = delay + lfo - d1;
    g1 = 1 - g2;
    
    indexD1 = index - d1;
    if (indexD1 < 1)
        indexD1 = indexD1 + MAX_BUFFER_SIZE;
    end
    
    indexD2 = index - d2;
    
    if (indexD2 < 1)
        indexD2 = indexD2 + MAX_BUFFER_SIZE;
    end
    
    y = g1 * delayBuffer(indexD1,1) + g2 * delayBuffer(indexD2,1);
    
    delayBuffer(index,1) = fbVar;
    
    if (index < MAX_BUFFER_SIZE - 1)
        index = index + 1;
    else
        index = 1;
    end
    
    out(n,1) = y;
    
end

freqz(out);