This is a MATLAB code that will s=use computer vision to determine the length of a certain finger. This happens through a specific template, but with some
work it can be modified to be very flexible and be usable with several templates.

It uses the SURF reference points in the computer vision framework from MATLAB to find where the finger starts and ends, 
and fronm that (and the measurement of pixels) the program is able to determine the length of the finger based on the picture and the template alone.

SOME FUTURE CHANGES:

-Instead of measuring the picture, create a new, modified picture that is now normalized (kind of what scanner apps do), and then measure using that and the template
-Expand and scale the program upwards
