![http://tubras.googlecode.com/svn/trunk/tools/irrb/irrbmodules/irrblend.png](http://tubras.googlecode.com/svn/trunk/tools/irrb/irrbmodules/irrblend.png)
The Irrlicht/Blender Exporter exports Blender scene and static node data to the native Irrlicht scene (.irr) and mesh (.irrmesh) file formats.

**Supported Blender Versions**
  * 2.48a, 2.49, 2.49a

**Implemented Features**
  * Blender Scene data is exported to Irrlicht native scene format (.irr).
  * Blender Mesh data is exported to the Irrlicht native mesh format (.irrmesh).
  * Export Blender ID Properties as Irrlicht scene UserData.
  * Export Blender Lamp, Mesh, Camera, and Empty objects.
  * Export Game Engine Materials and corresponding UV data.
  * Export Blender Generated Lightmap/Baked Materials.
  * Export Object Parent/Child relationships and transforms.
  * Export Irrlicht Skyboxes and Billboards.
  * Export Blender Mist as Irrlicht Fog.
  * Export Collsion/Physics data.
  * Specify Textures as two-sided, transparent, and/or using lighting per face.
  * Blender Packed UV Images may optionally be saved to a user specified location and format.
  * Automatic translation between Blender and Irrlicht coordinate systems.
  * Optionally "walk test" your scene immediately after it has been exported using the Irrlicht render engine.

**Change Log**
  * [changes.txt](http://tubras.googlecode.com/svn/trunk/tools/irrb/irrbmodules/docs/changes.txt)

**Tutorials**
  * [irrb Tutorials](http://code.google.com/p/tubras/wiki/irrbTutorials)


| ![http://tubras.googlecode.com/svn/wiki/images/irrb-0.4s.png](http://tubras.googlecode.com/svn/wiki/images/irrb-0.4s.png) |
|:--------------------------------------------------------------------------------------------------------------------------|
| [irrb-0.4.blend](http://tubras.googlecode.com/svn/trunk/tools/blendfiles/irrb-0.4.blend)                                  |


---

## Downloads ##

| **File** | **Size** | **Download Link** | **Description** |
|:---------|:---------|:------------------|:----------------|
| irrb-0.4.zip | 47.6 KB  | http://tubras.googlecode.com/files/irrb-0.4.zip | Irrlicht/Blender Exporter (**irrb**) |
| irrbUserGuide-0.4.pdf | 1.9 MB   | http://tubras.googlecode.com/files/irrbUserGuide-0.4.pdf | **irrb** User Guide |
| irrbUtils-0.4-win32.zip | 1.9 MB   | http://tubras.googlecode.com/files/irrbUtils-0.4-win32.zip | **irrb** Utilities for Windows |
| irrbUtils-0.4-linux32.zip | 3.6 MB   | http://tubras.googlecode.com/files/irrbUtils-0.4-linux32.zip | **irrb** Utilities for Linux |




---

## FAQ ##

**Q**: I have a question, where do I go?

**A**:  You may post **irrb** related questions in this [Irrlicht thread](http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=27073). Please read the **irrb** [UserGuide](http://tubras.googlecode.com/files/irrbUserGuide-0.3.pdf) before posting a question.

---

**Q**: Can I export animated meshes?

**A**: **Not Yet**.  The .irrmesh file format currently doesn't support animation.

---

**Q**: Can **irrb** invoke my own application instead of **iwalktest** after exporting?

**A**: **Yes.**  See the section "iwalktest Usage" in the **irrb** [UserGuide](http://tubras.googlecode.com/files/irrbUserGuide-0.3.pdf)

---

**Q**: Where can I report bugs?

**A**: [In the irrb Bug thread.](http://groups.google.com/group/tubras-development/browse_thread/thread/3ad2e7c3bc844ce1)

---

**Q**: Where can I submit a patch?

**A**: [In the irrb Patch thread.](http://groups.google.com/group/tubras-development/browse_thread/thread/e1592a41bf7b17d8)

---
