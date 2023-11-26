# <big>Robot Dance Project</big>
> [Name=XyQZ]


# Changelogs

## 2023-11-25

The colour of the triangle stopped showing. The console gives
```
OpenGL Error in D:\Codes\Proj\Yau-Lab\OpenGL1\src\MyGLCanvas.cpp: line 155: 湩慶楬⁤慶畬e
OpenGL Error in D:\Codes\Proj\Yau-Lab\OpenGL1\src\MyGLCanvas.cpp: line 160: 湩慶楬⁤灯牥瑡潩n
```
which I didn't understand. Maybe GLString is not explicitly convertible to wxString or char[].

#### Changes:
 * Put the shader compilation into a separate function called `getShader` in `shader.h` and `.cpp`. This checks out the todolist.
 * Added and constructed wxTimer but there is nothing in the `MyGLCanvas::OnTimer()` function yet.
#### TODO:
 * [x] Abstract and refactor the code from `MyGLCanvas.cpp`, separate it to `shaders.h` and `shaders.cpp`.
 * [x] use `wxTimer` to lock the framerate of `myGLCanvas` as now
   * it only redraw the frame on resizing the window, and 
   * resizing the window too much causes the app to lag.
 * [ ] Test various things for loading an `.OBJ` file into the canvas.
 * [x] Learn `glm` library for consequent usage.
 * [ ] Implement a button panel (`wxPanel` that overlaps with the current one looks better) or menubar (`wxMenubar`) for buttons to different things.
 * [ ] make a way so that it shows the realtime framerate in runtime, prob use `wxGetUTCTimeUSec()` or `wxGetLocalTimeMillis()`.
## 2023-11-24

There is no visible bugs in the project. 
#### Changes:
 * Refactored `utils.h` away, now as `openGLDebug.h` and `.cpp` that serve as 
#### TODO:
 * Abstract and refactor the code from `MyGLCanvas.cpp`, separate it to `shaders.h` and `shaders.cpp`.
 * use `wxTimer` to lock the framerate of `myGLCanvas` as now
   * it only redraw the frame on resizing the window, and 
   * resizing the window too much causes the app to lag.
 * Test various things for loading an `.OBJ` file into the canvas.
 * Learn `glm` library for consequent usage.
 * Implement a button panel (`wxPanel` that overlaps with the current one looks better) or menubar (`wxMenubar`) for buttons to different things.