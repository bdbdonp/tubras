[irrbTut2.blend](http://tubras.googlecode.com/svn/trunk/tools/blendfiles/irrbTut2.blend)

This tutorial demonstrates using three materials on a single mesh.  Note that you aren't limited to three materials per mesh, the fact is that it is possible to assign a different material to each **face** of a mesh.

Our intended goal is to produce the following scene:

![http://tubras.googlecode.com/svn/wiki/images/irrbss36.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss36.jpg)

This tutorial will use the following three images downloaded from [cgtextures.com](http://www.cgtextures.com/). Save them to the c:\irrbScenes\irrbTut2\tex\ directory:

![http://tubras.googlecode.com/svn/wiki/images/brick1.png](http://tubras.googlecode.com/svn/wiki/images/brick1.png)
![http://tubras.googlecode.com/svn/wiki/images/dirt1.png](http://tubras.googlecode.com/svn/wiki/images/dirt1.png)
![http://tubras.googlecode.com/svn/wiki/images/concrete1.png](http://tubras.googlecode.com/svn/wiki/images/concrete1.png)

Start with a new scene in Blender and resize the cube mesh to approximately 6x6 units.  From the Front View (**NUM1**), grab (**GKEY, ZKEY**) and move the cube up to align its bottom  to the red line.

Switch to edit mode and de-select the vertices (**AKEY**).  Box select the top vertices and move them down so the cube is approximately 4 units high.

Next we're going to do a Horizontal Loop Cut through the cube:

  * Select all of the vertices with the **AKEY**. All vertices will turn yellow when selected.
  * CTRL-RKEY to initiate the loop cut.
  * Move the mouse around the mesh until a horizontal, pink line appears
  * LMB and then slide the cut to just below the middle and then LMB to anchor the cut.

Here's what we should have so far:

![http://tubras.googlecode.com/svn/wiki/images/irrbss37.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss37.jpg)

Now we'll remove the top and front two faces:

  * Switch to Face Select Mode - **CTRL-TAB** and then select the "Faces" menu item.
  * **SHIFT-RMB** the top and front two faces.
  * **XKEY** and then select the "Faces" menu item to erase/delete the selected faces.

![http://tubras.googlecode.com/svn/wiki/images/irrbss38.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss38.jpg)

We can see from the above image that the face normals are facing out so we'll need to flip them:

  * **AKEY** to select all of the faces.
  * **WKEY** and then select the "Flip Normals" menu item.

![http://tubras.googlecode.com/svn/wiki/images/irrbss39.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss39.jpg)

Now we're ready to set up the materials.  We'll start with the ground plane and work our way up.

  * Enter Edit Mode - **TAB** when in Object Select Mode.
  * Enter Face Select Mode - **CTRL-TAB**, "Faces".
  * Select the ground plane - **RMB**.
  * Unwrap - UKEY.
  * Load the image "c:\irrbScenes\irrbTut2\tex\dirt1.png" into the UV/Image Editor.
  * Select (**AKEY**) all of the UV coordinates in the UV/Image Editor.
  * Size (**SKEY**) the UV coordinates to approximate two and times the original:

![http://tubras.googlecode.com/svn/wiki/images/irrbss40.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss40.jpg)

Next, while in Edit Mode, select the three lower panels of the walls and unwrap (**UKEY**):

![http://tubras.googlecode.com/svn/wiki/images/irrbss41.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss41.jpg)

You'll notice the quads are unwrapped sideways so we'll have to rotate them in order for the brick texture to appear correctly:

  * In the UV/Image Editor select all of the UV coordinates - **AKEY**.
  * Rotate (**RKEY**) the coordinates.  If you hold **CTRL** while rotating, the rotation will occur in steps of 5 degrees.

![http://tubras.googlecode.com/svn/wiki/images/irrbss42.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss42.jpg)

After the rotate, move (**GKEY**) the coordinates down to the bottom of the work area and then load the image "c:\irrbScenes\irrbTut2\tex\brick1.png":

![http://tubras.googlecode.com/svn/wiki/images/irrbss43.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss43.jpg)

We'll need to fix the "stretched" look by adjusting the UV coordinates:

  * De-select the UV coordinates - **AKEY**
  * Box select the top UV coordinates - **BKEY**, **LMB**, drag.
  * Move the top coordinates to the top of the image - **GKEY**, **YKEY**, drag, **LMB** to anchor.

![http://tubras.googlecode.com/svn/wiki/images/irrbss44.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss44.jpg)

To finish, we'll adjust the UV coordinates in the X direction:

  * Select all of the UV coordinates - **AKEY**, **AKEY**
  * Size the coordinates - **SKEY**, **XKEY**, drag, **LMB**.

![http://tubras.googlecode.com/svn/wiki/images/irrbss45.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss45.jpg)

Note that you may zoom in/out of the UV/Image Editor View by scrolling the mouse wheel.

To map the top half of the walls, repeat the steps that were used for mapping the brick.  The only difference is that you need to use the image "c:\irrbScenes\irrbTut2\tex\cement1.png" in place of the "brick1.png" image.

![http://tubras.googlecode.com/svn/wiki/images/irrbss46.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss46.jpg)

And finally our exported results:

![http://tubras.googlecode.com/svn/wiki/images/irrbss36.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss36.jpg)

---
