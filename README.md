# 2D Convex Hull Visualizer

[Demo Video](https://youtu.be/ysKY90w-4r8?si=kWAAfBrtOZyzJ7El)

2D visualisation of the step-by-step process of various Convex Hull algorithms. Made with C++, using Raysan5's Raylib for rendering, and RayGUI for the GUI 

### Implementation
* The concrete implementations of many of these algorithms usually involve quite a few nested loops, and I don't want to dirty up my update loop by placing a _render()_ call inside it.
* Thus, the approach taken was to, within the algorithm computing the convex hull, push an instance of **IAnimFrame2D** _(which contains information about what to draw)_ for each step of the convex hull, into a queue.
* During one update iteration, all the steps of the convex hull are computed and the cached
* Then, for each render() call, you can unload the **IAnimFrame2D's** one-by-one from the queue to display 

### Extra
* At the time of writing, there are only 2 algorithms concretely implemented _(**Jarvis March** & **Graham Scan**)_.
* However, the system is extensible. You only have to implement IConvexHull2D, as well as raise an event to set the current algorithm to be used.
* Using state pattern for the control flow of the application _(Idle, Generating Points, Animating....)_






