# <big>Robot Dance Project</big>
> [Name=XyQZ]


# Logs
### 2024-01-10

I finally fixed the problem where the texture loads as shit. It was a dumb logic error. The error was mainly in `VertexBufferLayout`, which was the one I wanted to look into after panicking for days.

#### TODO:
- Robot Dance.
  - [x] Finish doing textures:
    - [x] Fix bugs:
      - [x] Check The Bind for `VertexArray`.
  - [ ] Make a cache of GetUniformLocation in `Shader`.
  - [ ] Get to work on the 
    - [ ] coordinate system, and the 
    - [ ] Lighting system.
  - [ ] Write a little parse file to read an `OBJ` file.
  - [ ] test and desect the humanoid model.
  - [ ] Finally get to code the dance moves.
- Original to-do list:
  * [x] Abstract and refactor the code from `MyGLCanvas.cpp`, separate it to `shaders.h` and `shaders.cpp`.
    * [x] Move the code creating shaders into a function.
    * [x] Move the code creating program into a function.
  * [x] Use `wxTimer` to lock the framerate of `myGLCanvas`
    * [x] Create an instance of `wxTimer` as a member of `myGLCanvas`.
    * [x] Make it fire an `wxPaintEvent` everytime it notifies.
    * [ ] Change the `OnSize` function so that when the window is resized, wait until the next repaint to redraw the window.
  * [ ] Test various things for loading an `.OBJ` file.
    * [ ] Write a helper function that loads the file into an C++ STL storage.
    * [ ] Make the shader powerful enough to take objects in space.
    * [ ] put the object into the shader space and render it.
  * [x] Learn `glm` library for consequent usage.
  * [ ] Implement a button panel (`wxPanel` that overlaps with the current one looks better) or menubar (`wxMenuBar`) for buttons to different things, for different moves.
  * [ ] Make a way so that it shows the realtime framerate in runtime, prob use `wxGetUTCTimeUSec()` or `wxGetLocalTimeMillis()`.

### 2024-01-07
Had a mental breakdown and finally get back on track working on this project.

#### TODO:
- Robot Dance.
    - [ ] Finish doing textures:
    - [ ] Fix bugs:
        - [ ] Check The Bind for `VertexArray`.
    - [ ] Make a cache of GetUniformLocation in `Shader`.
    - [ ] Get to work on the 
    - [ ] coordinate system, and the 
    - [ ] Lighting system.
    - [ ] Write a little parse file to read an `OBJ` file.
    - [ ] test and desect the humanoid model.
    - [ ] Finally get to code the dance moves.
- Original to-do list:
    * [x] Abstract and refactor the code from `MyGLCanvas.cpp`, separate it to `shaders.h` and `shaders.cpp`.
     * [x] Move the code creating shaders into a function.
     * [x] Move the code creating program into a function.
    * [x] Use `wxTimer` to lock the framerate of `myGLCanvas`
     * [x] Create an instance of `wxTimer` as a member of `myGLCanvas`.
     * [x] Make it fire an `wxPaintEvent` everytime it notifies.
     * [ ] Change the `OnSize` function so that when the window is resized, wait until the next repaint to redraw the window.
    * [ ] Test various things for loading an `.OBJ` file.
     * [ ] Write a helper function that loads the file into an C++ STL storage.
     * [ ] Make the shader powerful enough to take objects in space.
     * [ ] put the object into the shader space and render it.
    * [x] Learn `glm` library for consequent usage.
    * [ ] Implement a button panel (`wxPanel` that overlaps with the current one looks better) or menubar (`wxMenuBar`) for buttons to different things, for different moves.
    * [ ] Make a way so that it shows the realtime framerate in runtime, prob use `wxGetUTCTimeUSec()` or `wxGetLocalTimeMillis()`.

### 2023-11-26
Turns out that it was the fallback shader on an NVidia graphics. I had forgotten about shader programs and deleted the code to link the program when refactoring the code of shader compilation.
#### What I did today:
 * Made the `wxTimer` work, and the glCanvas now refreshes every 30 milliseconds, which is about 33 hertz.
 * Put the shader program codes into `shader.h` and `.cpp`
 * Studied about the two shaders and realises that fragment shader is called far more times than vertex shader, and this should be beared in mind when optimising the shader code.
 * Inspected into the structure of an `.OBJ` file and an `.MTL` file and realised that we need `glm` to transform in space before our shader program can do anything sufficient to load an 3d object.
#### TODO:
 * [x] Abstract and refactor the code from `MyGLCanvas.cpp`, separate it to `shaders.h` and `shaders.cpp`.
   * [x] Move the code creating shaders into a function.
   * [x] Move the code creating program into a function.
 * [ ] Use `wxTimer` to lock the framerate of `myGLCanvas`
   * [x] Create an instance of `wxTimer` as a member of `myGLCanvas`.
   * [x] Make it fire an `wxPaintEvent` everytime it notifies.
   * [ ] Change the `OnSize` function so that when the window is resized, wait until the next repaint to redraw the window.
 * [ ] Test various things for loading an `.OBJ` file.
   * [ ] Write a helper function that loads the file into an C++ STL storage.
   * [ ] Make the shader powerful enough to take objects in space.
   * [ ] put the object into the shader space and render it.
 * [x] Learn `glm` library for consequent usage.
 * [ ] Implement a button panel (`wxPanel` that overlaps with the current one looks better) or menubar (`wxMenuBar`) for buttons to different things, for different moves.
 * [ ] Make a way so that it shows the realtime framerate in runtime, prob use `wxGetUTCTimeUSec()` or `wxGetLocalTimeMillis()`.

### 2023-11-25

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
 * [ ] Abstract and refactor the code from `MyGLCanvas.cpp`, separate it to `shaders.h` and `shaders.cpp`.
   * [x] Move the code creating shaders into a function.
   * [ ] Move the code creating program into a function.
 * [ ] Use `wxTimer` to lock the framerate of `myGLCanvas`
   * [x] Create an instance of `wxTimer` as a member of `myGLCanvas`.
   * [ ] Make it fire an `wxPaintEvent` everytime it notifies.
   * [ ] Change the `OnSize` function so that when the window is resized, wait until the next repaint to redraw the window.
 * [ ] Test various things for loading an `.OBJ` file into the canvas.
 * [x] Learn `glm` library for consequent usage.
 * [ ] Implement a button panel (`wxPanel` that overlaps with the current one looks better) or menubar (`wxMenuBar`) for buttons to different things.
 * [ ] Make a way so that it shows the realtime framerate in runtime, prob use `wxGetUTCTimeUSec()` or `wxGetLocalTimeMillis()`.
### 2023-11-24

There is no visible bugs in the project. 
#### Changes:
 * Refactored `utils.h` away, now as `openGLDebug.h` and `.cpp` that serve as 
#### TODO:
 * Abstract and refactor the code from `MyGLCanvas.cpp`, separate it to `shaders.h` and `shaders.cpp`.
 * Use `wxTimer` to lock the framerate of `myGLCanvas` as now
   * it only redraw the frame on resizing the window, and 
   * resizing the window too much causes the app to lag.
 * Test various things for loading an `.OBJ` file into the canvas.
 * Learn `glm` library for consequent usage.
 * Implement a button panel (`wxPanel` that overlaps with the current one looks better) or menubar (`wxMenubar`) for buttons to different things.