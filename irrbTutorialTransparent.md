[irrbTut3.blend](http://tubras.googlecode.com/svn/trunk/tools/blendfiles/irrbTut3.blend)

To illustrate transparent materials, we'll use our work from the second Tutorial and add a transparent fence to the front of the scene:

![http://tubras.googlecode.com/svn/wiki/images/irrbss47.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss47.jpg)


Before you start, copy the .blend file and images from "irrbTut2" to the "c:\irrbScenes\irrbTut3" directory. Also save the following image to the "irrbTu3\images" directory as "chainlink.png".  This image was originally downloaded from [filterforge.com](http://www.filterforge.com/filters/871.html)

![http://tubras.googlecode.com/svn/wiki/images/chainlink.png](http://tubras.googlecode.com/svn/wiki/images/chainlink.png)

First we'll create and position the plane that the chain link texture will be mapped to:

  * In Object Mode, de-select everything - **AKEY**
  * Switch to Front View - **NUM1**.
  * Add a plane - **SPACE**, Add, Mesh, Plane.
  * Size the plane to the width of the current scene.  Adjust its height to approximately half of the current scene.
  * Position the plane to the front of the scene.

![http://tubras.googlecode.com/svn/wiki/images/irrbss48.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss48.jpg)

Next, we'll assign the image to the plane face:

  * Switch to Front View - **NUM1**.
  * Switch to Edit Mode - **TAB** when in Object Mode.
  * Unwrap - **UKEY**, Project from View (Bounds).
  * Load the c:\irrbScenes\irrbTut3\images\chainlin.png" image.
  * Adjust the size of the UV coordinates to obtain the appropriate tiling.

![http://tubras.googlecode.com/svn/wiki/images/irrbss49.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss49.jpg)

In order for **irrb** to export this material as a transparent material, we need to assign the UV Layer Name a name that corresponds to an Irrlicht transparent material name.  We can use either "trans\_alphach" (better quality) or "trans\_alphach\_ref" (more efficient).  For our example, we'll use "trans\_alphach".

That's it.  Now you're ready to export and view in **iwalktest**:

![http://tubras.googlecode.com/svn/wiki/images/irrbss47.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss47.jpg)


---
