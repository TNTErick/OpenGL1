# <big>Robot Dance Project</big>
> [Name=XyQZ]


# Changelogs
## Change Log 2023-11-24

There is no visible bugs in the project. TODO:
 * Abstract and refactor the code from `MyGLCanvas.cpp`, separate it to `shaders.h` and `shaders.cpp`.
 * use `wxTimer` to lock the framerate of `myGLCanvas` as now
   * it only redraw the frame on resizing the window, and 
   * resizing the window too much causes the app to lag.
 * Test various things for loading an `.OBJ` file into the canvas.
 * Learn `glm` library for consequent usage.
 * Implement a button panel (`wxPanel`) or menubar (`wxMenubar`) for buttons to different things.