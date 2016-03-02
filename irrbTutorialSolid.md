[irrbTut1.blend](http://tubras.googlecode.com/svn/trunk/tools/blendfiles/irrbTut1.blend)

This tutorial will generate two simple plane meshes, each containing a single UV mapped texture.  This type of material is known as an Irrlicht "**solid**" material. Our end result will look similar to this:

![http://tubras.googlecode.com/svn/wiki/images/irrbss35.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss35.jpg)

The first plane will use this image:

![http://tubras.googlecode.com/svn/wiki/images/stone1.png](http://tubras.googlecode.com/svn/wiki/images/stone1.png)

Save this image to the directory: "c:\irrbScenes\irrbTut1\tex".

The second plane will use an image that we procedurally generate, bake, and save using Blenders material system.  Let's get started.

Fire up Blender and split your screen by right clicking near the top of the 3D view and selecting the "Split Area" menu item.  Move the divider to the center and left click to anchor it.


I find it convenient to add the 3D View and UV/Image Editor split to my list of available screens in the default layout.  That way I can **CTRL-LEFT/RIGHT** between screens very quickly.  Here's a good tutorial on setting up custom screens:

http://blendernewbies.blogspot.com/2006/10/video-power-of-blender-screens.html

Set the right hand window to be the UV/Image editor:

![http://tubras.googlecode.com/svn/wiki/images/irrbss19.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss19.jpg)

In the 3D view window (left side), delete the default cube (right click to select, and **XKEY** or "Delete" to delete).

From the top view (**NUM7**), add a Plane mesh (**SPACE**, Add, Mesh, Plane).  Size the mesh to be approximate 8x8 units (**SKEY** - size, and left click to set the new size):

![http://tubras.googlecode.com/svn/wiki/images/irrbss20.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss20.jpg)

Create UV Coordinates:

  * In Edit Mode (**TAB** to switch between edit and object mode).
  * CTRL-TAB-3 to switch to Face Select Mode.
  * AKEY to select All faces.
  * UKEY to calculate UV's using a simple unwrap.

![http://tubras.googlecode.com/svn/wiki/images/irrbss21.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss21.jpg)

Now we're going to assign the previously saved stone1.png image to the UV map that was just created.  In the UV/Image editor window:

  * Select the menu Image | Open.
  * Navigate to and open c:\irrbScenes\irrTut1\tex\stone1.png

![http://tubras.googlecode.com/svn/wiki/images/irrbss22.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss22.jpg)

Next we'll scale the UV coordinates a little to tile the image a bit:

  * With the cursor over the UV/Image editor.
  * **AKEY** to select all of the UV coordinates.
  * **SKEY** to scale the coordinates.
  * Drag the mouse to about 3 times the original size.

![http://tubras.googlecode.com/svn/wiki/images/irrbss23.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss23.jpg)

Depicted in the image above, we also set the Irrlicht material type to "solid" by changing the UV layer name to "solid".

Let's take a quick look at the work we've done so far by exporting the scene and viewing it in Irrlicht (iwalktest):

  * Change the right hand window to "Scripts".
  * Select the Irrlicht exporter.
  * Click the "Export" button.

![http://tubras.googlecode.com/svn/wiki/images/irrbss24.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss24.jpg)

Congratulations on your first **irrb** generated scene!

Next we'll add another plane mesh to our scene and texture it using Blenders procedural materials and texture baking.

First we'll add the second plane:

  * Position the mouse over the 3D view window.
  * De-select the existing plane.  Failing to do so will add the new plane geometry to the existing one.
  * Switch to the front view - **NUM1**.
  * Add another plane - **SPACE**, Add, Mesh, Plane.

Next we'll position and size the second plane.  First positioning:

  * Switch to Object Mode - **TAB**.
  * Grab (**GKEY**) and then the **ZKEY** to constrain movement to the Z axis (up/down).  Position the bottom of the plane so it's just a little bit higher than the first plane. **LMB** when done.
  * Position the view to behind the camera (**MMB** and drag). Grab (**GKEY**) the second plane again and press the **YKEY** to constrain movement to the Y axis.  Move the plane to the back edge of the first plane and **LMB** when done:

![http://tubras.googlecode.com/svn/wiki/images/irrbss25.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss25.jpg)

Resize the second plane along the X axis:

  * Switch to Front View - **NUM1**.
  * Hit the **SKEY** to size, and **XKEY** to constrain the sizing along the X axis.
  * Drag the cursor until the plane is about 8 units wide. **LMB** when done.

Resize the height:

  * While still in Front View, hit the **TAB** key to place the second plane in Edit Mode.
  * De-select all of the vertices - **AKEY** (vertices will be pink).
  * Select the top 2 vertices either by using **SHIFT-RMB** on both of them or using the box select (**BKEY**, **LMB**, and drag).
  * Grab (**GKEY**) and then the **ZKEY** to constrain the vertex movement to the Z axis.  Position the vertices about 4 units up from the bottom.

![http://tubras.googlecode.com/svn/wiki/images/irrbss26.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss26.jpg)

**MMB** and drag behind the camera again. Our scene should now look like this:

![http://tubras.googlecode.com/svn/wiki/images/irrbss27.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss27.jpg)

Now we're ready to create a procedural/render material for the second plane. First we'll create UV coordinates for the second plane:

  * Cursor left window (3D View).
  * Switch the second plane into Edit Mode - **TAB**.
  * Switch to Front View - **NUM1**.
  * **AKEY** to select all of the faces (only 1) - dotted white line will appear around the selection.  If no dotted line, **AKEY** again.
  * **UKEY** to call up the UV Calculation menu.
  * Select the menu item "Project from View (Bounds)".

Now we can create an empty image to bake the material on:

  * Reset the right window to display the UV/Image Editor - Cursor over the right window, **SHIFT-F10**.
  * From the UV Editor menu select Image, New.  Set the new image parameters to 512x256 with an alpha of 1.0.  You will then see a new black image in the UV/Image Editor.

![http://tubras.googlecode.com/svn/wiki/images/irrbss28.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss28.jpg)

Next we'll create a new Blender material to bake onto the newly created image.  First add a new material in the Material Window:

![http://tubras.googlecode.com/svn/wiki/images/irrbss29.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss29.jpg)

And then add a new procedural texture to that material (2).

Next switch to the Texture Window - **F6**, and add a new texture type of "Clouds".

![http://tubras.googlecode.com/svn/wiki/images/irrbss30.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss30.jpg)

**F5** back to the Material Window and adjust the "Map To" color to a dark gray:

![http://tubras.googlecode.com/svn/wiki/images/irrbss31.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss31.jpg)

Now we have a Blender "Cloud" material that is ready to be baked onto the new image that was previously created for the second plane:

![http://tubras.googlecode.com/svn/wiki/images/irrbss32.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss32.jpg)

To actually bake the material, select from the top menu: Render, Bake, Texture Only.  Make sure you select "Texture Only" because we don't want any lighting to be baked in along with the texture.  The other bake options should make you a little excited though :)

Here's the result of the bake:

![http://tubras.googlecode.com/svn/wiki/images/irrbss33.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss33.jpg)

Before we export the scene, we need to save the newly created/baked image.  You can do this by either:

  * Select "Image", "Save As" from the UV/Image Editor menu. Or
  * Place the cursor in the UV/Image Editor and press **ALT-SKEY**.

Save the image to:  c:\irrbScenes\irrbTut1\tex\cloud.png.  Make sure you set the image type to "PNG":

![http://tubras.googlecode.com/svn/wiki/images/irrbss34.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss34.jpg)

Note if you decide to re-bake an image, you will need to re-save it in order for the updated image to appear in **iwalktest**.

Now you're ready to export and view in **iwalktest**:

![http://tubras.googlecode.com/svn/wiki/images/irrbss35.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss35.jpg)

wysiwyg baby, wysiwyg...


---
