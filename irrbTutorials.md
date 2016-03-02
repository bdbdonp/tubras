## Introduction ##

Here you will find several tutorials on how to use **irrb** 0.4 in Blender (version 2.49a).

The tutorials on this wiki are **NOT** intended to teach you how to use Blender. Even though the tutorials may mention Blender key combinations and mouse buttons for certain functionality, you will be doing yourself a big favor by spending a little time learning the **[basics of Blender](http://www.blender.org/education-help/)**. The **[Blender Wiki Manual](http://wiki.blender.org/index.php/Doc:Manual)** is a very good place to start for beginners.

Before proceeding with a particular tutorial, please review the [Tutorial Setup](irrbTutorials#Tutorial_Setup.md) located in the next section.

## irrb Tutorials ##
| **Tutorial** | **Description** |
|:-------------|:----------------|
| [Solid Material](http://code.google.com/p/tubras/wiki/irrbTutorialSolid) | This basic tutorial will walk you through mapping a single UV texture.  The second half the tutorial will show you how to bake a Blender Procedural Material onto a UV image. |
| [Multiple Materials](http://code.google.com/p/tubras/wiki/irrbTutorialMultiSolid) | This tutorial will show you how to map multiple UV textures onto a single mesh. |
| [Transparent Material](http://code.google.com/p/tubras/wiki/irrbTutorialTransparent) | This tutorial will show you how to create and export a transparent material. |
| [Basic Light Mapping](http://code.google.com/p/tubras/wiki/irrbTutorialLightmap) | This tutorial will show you how to generate a lightmap in a second UV layer. |

## Blender Tutorials and Links ##
[Blender Art Magazine](http://www.blenderart.org). The Blender Art Magazine is a free resource for learning all things Blender.  A complete list of available issues may be found here: [Issue List](http://www.blenderart.org/issues/).

[MONTAGE STUDIO](http://www.montagestudio.org/Welcome.html). Jonathan Williamson has created a very good (and free) tutorial on [Modeling a Lowpoly Character](http://www.montagestudio.org/Tutorials.html).



---


### Tutorial Setup ###

The tutorials will use the **irrb Utilities** for viewing the exporter results. Installation instructions for the utilities may found in the **irrb** [User Guide](http://tubras.googlecode.com/files/irrbUserGuide-0.4.pdf).

Each of **irrb** tutorials assume the following directory structure for exported content:

```
c:\irrbScenes
   |
   | --- irrbTut1
   | ------ mdl
   | ------ tex
   |
   | --- irrbTut2
   | ------ mdl
   | ------ tex
```

The scene file (Scene.irr) will be created inside of the specific tutorial subdirectory.  For **irrbTut1**, this will be "c:\irrbScenes\irrbTut1\Scene.irr".  Each scenes mesh data will be saved inside of the "mdl" sub-directory underneath the appropriate tutorial.  The same holds true for related images ("tex" sub-directory).

For **irrbTut1**, the Output Directory would be setup as follows:

![http://tubras.googlecode.com/svn/wiki/images/irrbss17.png](http://tubras.googlecode.com/svn/wiki/images/irrbss17.png)


---
