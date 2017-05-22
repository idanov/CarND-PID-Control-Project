# Report on my findings on PID

## Choice of parameters

After implementing twiddle and a lot of manual tweaking and automatic twiddling, I have settled
on the following parameter setup:
```
Kp = 5
Ki = 0.001
Kd = 50
```
A video with that setup can be found [here](https://youtu.be/K_NJrIhNHv0).

## Effect of Kp

By observing different values of `Kp`, I have noticed that higher values result in more rapid
course corrections which cause very unstable and wiggly behaviour especially in track segments
with high curvature. Lower values of `Kp` on the other hand result in slow responses to changes of
course and very hard or impossible for the car to keep up with curves on the track. Here one
can see two videos with `Kp` set to `0.5` and `15` respectively:

[Video for Kp = 0.5 here](https://youtu.be/NGe3C0Uk0Vo)

[Video for Kp = 15 here](https://youtu.be/AcrsdiclaCc)

## Effect of I

`Ki` has the effect of keeping the course of the car stable over the long term by compensating
the systematic bias. Therefore high values result in catastrophic results visible from
the beginning of the run, where lower values are not noticed until longer periods have passed.
In the current setup, there seems to be only a very small systematic bias which could be witnessed
only after a few laps with `Ki` set to `0` and expressing themselves by causing high amplitudes
of the oscillations before stabilizing the car after curves. However `Ki` set to `1` results in very
drastic issues arising from overcompensating not only for the bias, but also for the variance of the error.

[Video for Ki = 0 here](https://youtu.be/QIR5BQib4-w)

[Vide for Ki = 1 here](https://youtu.be/CI2Jm3TZW9I)

## Effect of D

`Kd` is used to counterbalance the effects of `Kp` by smoothing out any overshooting caused by it.
A good combination of `Kp` and `Kd` results in smooth course corrections and evanescent oscillations.
Too high `Kd` results in high frequency and low amplitude oscillations, which cause the car to follow
the course too strictly at the expense of constant alternating (and possibly unpleasant to humans)
steering, preventing the acceleration of the car beyond 4mph. Low `Kd` values on the other hand make
the car unstable and unable to recover quickly from the corrections caused by `Kp`.

[Video for Kd = 5 here](https://youtu.be/tLr-w99Z5Tg)

[Video for Kd = 500 here](https://youtu.be/PmOQId5CL3A)
