[irrbTut4.blend](http://tubras.googlecode.com/svn/trunk/tools/blendfiles/irrbTut4.blend)

Preliminary light-mapping caveats and notes:

  * Light mapping should be the last step performed before exporting a scene. If you modify geometry after light mapping a scene, the light mapping will need to be redone.
  * Light mapping should only be performed on static geometry.  Movable objects should be set to **NOT** cast shadows.
  * Texture first, light map second.
  * The technique we'll use for light mapping involves render baking onto a second UV  "light map" layer.

This tutorial will light map a simple scene consisting of a plane and a couple of cubes:

![http://tubras.googlecode.com/svn/wiki/images/irrbss51.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss51.jpg)

We will use the following two images downloaded from [cgtextures.com](http://www.cgtextures.com). Save them to the c:\irrbScenes\irrbTut3\images directory:

![http://tubras.googlecode.com/svn/wiki/images/tile.png](http://tubras.googlecode.com/svn/wiki/images/tile.png)
![http://tubras.googlecode.com/svn/wiki/images/wood.png](http://tubras.googlecode.com/svn/wiki/images/wood.png)

Start with a new scene (cube already exists) and add a plane mesh approximately 12x12 units in size.

Before we create the light map, we'll UV map the base/diffuse textures.  First the plane:

  * In Edit Mode, **AKEY** to select of the vertices.
  * **UKEY** to unwrap.
  * In the UV/Image Editor, open and assign the previously saved tile.png image (c:\irrbScenes\irrbTut4\images\tile.png).  Resize the UV coordinates to approximately 3X the original size: With the cursor in the UV/Image Editor - **SKEY**, **3KEY**.

![http://tubras.googlecode.com/svn/wiki/images/irrbss52.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss52.jpg)

Next we'll create the base/diffuse texture for the cube:

  * Select the cube in Edit Mode.
  * **AKEY** to select all of the vertices.
  * **UKEY** to call up the UV Calculation Menu and then select "Unwrap".
  * In the UV/Image Editor, open and assign the previously saved wood.png image (c:\irrbScenes\irrbTut4\images\wood.png).

![http://tubras.googlecode.com/svn/wiki/images/irrbss53.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss53.jpg)

Now we'll add a second cube by duplicating the first cube (including the UV mapped texture):

  * Select the original cube in Object Mode.
  * **SHIFT-DKEY** to duplicate.  Move the cube and **LMB** to anchor it.
  * Switch to Front View - **NUM1**.
  * Select both cubes - **SHIFT-RMB**.
  * Move them up so the bottoms are barely touching the floor - **GKEY**, **ZKEY**, move the mouse and **LMB** to anchor.
  * Rotate the second cube 45 degrees: **RMB** to select, **NUM7** to switch to top view, **RKEY** to start the rotation, move the mouse to rotate approximately 45 degrees.  **LMB** when done.

If exported, the scene should appear as follows:

![http://tubras.googlecode.com/svn/wiki/images/irrbss54.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss54.jpg)

Because we want to use a single light map image for the entire scene, we need to join all of the meshes into one single mesh:

  * In Object Mode select all of the meshes - **SHIFT-RMB** (clicking on each object).
  * Join the meshes together - **CTRL-JKEY**.

Note that even though the meshes are now joined into a single mesh, the individual faces retain the original UV/Image mapping.

Now we are ready to create and map the light map UV layer:

  * In Object Mode select the newly joined mesh - **RMB**.
  * Switch to Edit Mode - **TAB**.
  * Add a **new** UV Layer:

![http://tubras.googlecode.com/svn/wiki/images/irrbss55.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss55.jpg)

Then set it as the "rendering texture/target":

![http://tubras.googlecode.com/svn/wiki/images/irrbss56.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss56.jpg)

Now we're ready to create the light map image, bake, and finally save the newly generated lightmap image.

  * In the UV/Image Editor, create a new image 512x512.
  * In the 3D Window, create the light map UV coordinates for the second UV layer - **UKEY** and then select the "**Lightmap UVPack**" menu item.
  * Bake the light map into the second UV layer - **CTRL-ALT-BKEY** and then select the "Full Render" menu item

The light map layer should look similar to this:

![http://tubras.googlecode.com/svn/wiki/images/irrbss57.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss57.jpg)

In the UV/Image Editor save the newly baked light map image to c:\irrbScenes\irrbTut4\images\lightmap.png.

Finally, we need to _tell_ **irrb** to export this material as a light map material. To do this, we need to assign the UV Layer Name a name that corresponds to an Irrlicht light map material name: **lightmap**, **lightmap\_m2**, **lightmap\_m4**, **lightmap\_light** etc.  See the section on [Irrlicht Material Information](http://code.google.com/p/tubras/wiki/irrb#Irrlicht_Material_Generation) for more info.

We'll use "lightmap" for our example:

![http://tubras.googlecode.com/svn/wiki/images/irrbss58.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss58.jpg)

Now we're ready to export and view in **iwalktest**:

![http://tubras.googlecode.com/svn/wiki/images/irrbss59.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss59.jpg)

Hmmm, you may have noticed the shadows from the cubes are completely black.  This is because we didn't set up any ambient light for our scene.  Let's do that now.

Call up the Materials Window - **F5KEY**, and select the "World" buttons.  Then set the Ambient RGB values to 0.2:

![http://tubras.googlecode.com/svn/wiki/images/irrbss60.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss60.jpg)

Now we'll need to re-bake the light map and re-save it:

  * Re-bake the light map image - **CTRL-ALT-BKEY**, and then select the "Full Render" menu item.
  * Save the newly baked light map image over the top of the existing lightmap.png. In the UV/Image Editor window - **ALT-SKEY**.

Re-export and view your results:

![http://tubras.googlecode.com/svn/wiki/images/irrbss61.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss61.jpg)

Are we done? Not really.  There are still a couple of problems.

**Jagged Shadow Edges**.  We can improve the edges by increasing the "sampling" value for the lights that generate shadows.  In our case we have a single lamp that we'll modify:

  * Select the light - **RMB**.
  * Switch to the Materials panel **F5KEY**.
  * Modify the samples from the default value of 1 to 16.

![http://tubras.googlecode.com/svn/wiki/images/irrbss66.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss66.jpg)

Re-bake the lightmap with the new settings, save the generated lightmap, and then re-export:

![http://tubras.googlecode.com/svn/wiki/images/irrbss64.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss64.jpg)

**Single Static Mesh**.  Our scene is now a single static mesh which isn't very efficient for culling.  In order to increase the culling efficiency, we need to separate the mesh out into individual meshes.  Fortunately, Blender retains the UV coordinate/image info even after separating out individual meshes.  To separate:

  * In Edit Mode (Faces) select the faces you want to extract out into a separate mesh, **PKEY**, and then choose the "Selected" menu item.

Now you're ready to experiment and add some colored spot lights:

![http://tubras.googlecode.com/svn/wiki/images/irrbss65.jpg](http://tubras.googlecode.com/svn/wiki/images/irrbss65.jpg)


---
