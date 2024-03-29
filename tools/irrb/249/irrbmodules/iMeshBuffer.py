#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------
import Blender
import iUtils
import iMaterials
import iGUI

#-----------------------------------------------------------------------------
#                                  V e r t e x
#-----------------------------------------------------------------------------
class Vertex:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bVertex, irrIdx, bKeyBlocks, color, tangent):
        self.bVertex = bVertex
        self.index = bVertex.index
        self.irrIdx = irrIdx
        self.vSColor = color
        self.UV = [Blender.Mathutils.Vector(0.0,0.0,0.0), \
                Blender.Mathutils.Vector(0.0,0.0,0.0)]
        v = self.bVertex.co
        #
        # if shape keys exist, use the position from the "basis" key.
        #
        self.pos = []
        if bKeyBlocks != None:
            self.pos = []
            for i in range(len(bKeyBlocks)):
                v = bKeyBlocks[i].data[bVertex.index]
                self.pos.append(v)
        else:
            self.pos.append(v)
        n = self.bVertex.no
        self.normal = Blender.Mathutils.Vector(n.x,n.y,n.z)
        if tangent != None:
            self.tangent = Blender.Mathutils.Vector(tangent.x, tangent.y,
                    tangent.z)
        else:
            self.tangent = Blender.Mathutils.Vector(0, 0, 0)

        self.biNormal = Blender.Mathutils.CrossVecs(self.normal,self.tangent)
        self.biNormal.normalize()
                
#-----------------------------------------------------------------------------
#                               M e s h B u f f e r
#-----------------------------------------------------------------------------
class MeshBuffer:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bMesh, material, uvMatName, bufNumber):
        self.bMesh = bMesh

        self.bKey = self.bMesh.key
        self.bKeyBlocks = None
        if self.bKey:
            self.bKeyBlocks = self.bKey.blocks

        self.bufNumber = bufNumber

        self.material = material
        self.uvMatName = uvMatName
        self.vertices = []  # list of vertices 
        self.faces = []     # list of irr indexes {{i0,i1,i2},{},...}
        self.vertDict = {}  # blender vert index : internal Vertex()
        self.hasFaceUV = bMesh.faceUV
        self.uvLayers = bMesh.getUVLayerNames()
        self.activeUVLayer = bMesh.activeUVLayer
        
    #-------------------------------------------------------------------------
    #                         g e t M a t e r i a l T y p e
    #-------------------------------------------------------------------------
    def getMaterialType(self):
        return self.material.getType()

    #-------------------------------------------------------------------------
    #                            g e t M a t e r i a l
    #-------------------------------------------------------------------------
    def getMaterial(self):
        return self.material
    
    #-------------------------------------------------------------------------
    #                             a d d V e r t e x
    #-------------------------------------------------------------------------
    def addVertex(self, bVertex):

        vertex = Vertex(bVertex)

        self.vertices.append(vertex)

        # return our index
        return len(self.vertices)

    #-------------------------------------------------------------------------
    #                             g e t V e r t e x
    #-------------------------------------------------------------------------
    def getVertex(self,bFace,idx,bKeyBlocks,tangent):

        #
        # extract the Blender vertex data
        #
        bVertex = bFace.v[idx]
        vColor = None
        if self.bMesh.vertexColors:
            fColor = bFace.col[idx]
            vColor = iUtils.rgba2SColor((fColor.r, fColor.g, fColor.b,
                fColor.a))

        # if uv's present - every vertex is unique.  should check for 
        # equal uv's...
        if self.hasFaceUV and (bFace.mode & iUtils.B_MESH_FACEMODE_TEX):
            uvLayerNames = self.bMesh.getUVLayerNames()
            vertex = Vertex(bVertex,len(self.vertices),bKeyBlocks, vColor,
                    tangent)
            self.bMesh.activeUVLayer = uvLayerNames[0]
            vertex.UV[0] = bFace.uv[idx]
            if len(uvLayerNames) > 1:
               self.bMesh.activeUVLayer = uvLayerNames[1]
               vertex.UV[1] = bFace.uv[idx]
               self.bMesh.activeUVLayer = self.activeUVLayer

            self.vertices.append(vertex)
        else:
            if bVertex.index in self.vertDict:
                vertex = self.vertDict[bVertex.index]
            else:
                vertex = Vertex(bVertex,len(self.vertices),bKeyBlocks,
                        vColor, None)
                self.vertDict[bVertex.index] = vertex
                self.vertices.append(vertex)

        #
        # fix up vertex coords with basis shape if it exists
        #
        #adjust vertex coords if keyblock exists
        #if bKeyBlocks:
        #   bVertex = bKeyBlocks[0].data[idx]

        return vertex

    #-------------------------------------------------------------------------
    #                              a d d F a c e
    #-------------------------------------------------------------------------
    def addFace(self, bFace, faceTangents, bKeyBlocks):

        if (len(bFace.v) == 3):
            v1 = self.getVertex(bFace,0,bKeyBlocks,faceTangents[0])
            v2 = self.getVertex(bFace,1,bKeyBlocks,faceTangents[1])
            v3 = self.getVertex(bFace,2,bKeyBlocks,faceTangents[2])
            self.faces.append((v1.irrIdx, v2.irrIdx, v3.irrIdx))
        elif (len(bFace.v) == 4):
            v1 = self.getVertex(bFace,0,bKeyBlocks,faceTangents[0])
            v2 = self.getVertex(bFace,1,bKeyBlocks,faceTangents[1])
            v3 = self.getVertex(bFace,2,bKeyBlocks,faceTangents[2])
            v4 = self.getVertex(bFace,3,bKeyBlocks,faceTangents[3])
            self.faces.append((v1.irrIdx, v2.irrIdx, v3.irrIdx))
            self.faces.append((v4.irrIdx, v1.irrIdx, v3.irrIdx))
        else:
            print('Ignored face with %d edges.' % len(bFace.v))

    #-------------------------------------------------------------------------
    #                        _ w r i t e V e r t e x
    #-------------------------------------------------------------------------
    def _writeVertex(self, file, vert, vtype, idx=0):
        pos = vert.pos[idx]
        normal = vert.normal
        color = vert.vSColor
        uv = vert.UV[0]
        uv2 = vert.UV[1]
        tangent = vert.tangent
        binormal = vert.biNormal

        spos = '%.6f %.6f %.6f ' % (pos.x, pos.z, pos.y)
        snormal = '%.6f %.6f %.6f ' % (normal.x, normal.z, normal.y)

        if color != None and self.material.useVertexColor:
            scolor = iUtils.colour2str(color) + ' '
        else:
            scolor = iUtils.del2SColor(self.material.getDiffuse()) + ' '
        suv = '%.6f %.6f ' % (uv.x, 1-uv.y)

        if vtype == iMaterials.EVT_STANDARD:
            file.write('         ' + spos + snormal + scolor + suv + '\n')
            return

        if vtype == iMaterials.EVT_2TCOORDS:
            suv2 = '%.6f %.6f' % (uv2.x, 1-uv2.y)
            file.write('         ' + spos + snormal + scolor + suv + suv2 + '\n')
            return

        stangent = '%.6f %.6f %.6f ' % (tangent.x, tangent.z, tangent.y)
        sbinormal = '%.6f %.6f %.6f' % (binormal.x, binormal.z, binormal.y)
        file.write('         ' + spos + snormal + scolor + suv + stangent + sbinormal + '\n')

    #-------------------------------------------------------------------------
    #                       _ w r i t e V e r t i c e s
    #-------------------------------------------------------------------------
    def _writeVertices(self, file):
        vtype = self.material.getVertexType()
        
        if vtype == iMaterials.EVT_STANDARD:
            svtype = 'standard'
        elif vtype == iMaterials.EVT_2TCOORDS:
            svtype = '2tcoords'
        elif vtype == iMaterials.EVT_TANGENTS:
            svtype = 'tangents'

        file.write('      <vertices type="%s" vertexCount="%d">\n' % 
                (svtype, len(self.vertices)))

        meshName = self.bMesh.name
        tverts = len(self.vertices)
        vcount = 0
        mcount = 100
        bnum = self.bufNumber
        if tverts > 10000:
            mcount = 1000
        for vert in self.vertices:
            if iGUI.exportCancelled():
                return
            
            self._writeVertex(file, vert, vtype)
            vcount += 1
            if (vcount % mcount) == 0:
                iGUI.updateStatus('Exporting Mesh: %s, buf: %d writing vertices(%d of %d)' % 
                        (meshName, bnum, vcount, tverts))
        file.write('      </vertices>\n')        

    #-------------------------------------------------------------------------
    #                         _ w r i t e F a c e s
    #-------------------------------------------------------------------------
    def _writeFaces(self, file):
        file.write('      <indices indexCount="%d">\n' % (len(self.faces)*3))
        line = '        '
        iCount = 0

        meshName = self.bMesh.name
        tfaces = len(self.faces)
        fcount = 0
        bnum = self.bufNumber
        for face in self.faces:
            if iGUI.exportCancelled():
                return
            line += (' %d %d %d' % (face[2], face[1], face[0]))
            iCount += 1
            if iCount == 12:
                line += '\n'
                file.write(line)
                line = '        '
                iCount = 0
            fcount += 1
            if (fcount % 100) == 0:
                iGUI.updateStatus('Exporting Mesh: %s, buf: %d writing faces(%d of %d)' % 
                        (meshName, bnum, fcount, tfaces))


        if iCount > 0:
            line += '\n'
            file.write(line)

        file.write('      </indices>\n')

    #-------------------------------------------------------------------------
    #                     _ w r i t e M o r p h T a r g e t
    #-------------------------------------------------------------------------
    def _writeMorphTarget(self, file, idx):
        block = self.bKeyBlocks[idx]

        #
        # first, count the number of vertices we'll be writing
        #

        vidx = 0
        for vert in self.vertices:
            if iGUI.exportCancelled():
                return

            bvert = vert.pos[0]
            pos = vert.pos[idx]

            if (bvert.x != pos.x) or (bvert.y != pos.y) or (bvert.z != pos.z):
                vidx += 1

        file.write('      <morph-target name="%s" vertexCount="%d">\n' % (block.name,vidx))

        meshName = self.bMesh.name
        tverts = len(self.vertices)
        vcount = 0
        mcount = 100
        bnum = self.bufNumber
        if tverts > 10000:
            mcount = 1000
        vidx = 0
        for vert in self.vertices:
            if iGUI.exportCancelled():
                return

            bvert = vert.pos[0]
            
            pos = vert.pos[idx]

            if (bvert.x != pos.x) or (bvert.y != pos.y) or (bvert.z != pos.z):
                spos = '%d %.6f %.6f %.6f ' % (vidx, pos.x, pos.z, pos.y)
                file.write('         ' + spos + '\n')
            vidx += 1
            vcount += 1
            if (vcount % mcount) == 0:
                iGUI.updateStatus('Exporting Mesh: %s, buf: %d writing vertices(%d of %d)' % 
                        (meshName, bnum, vcount, tverts))

        file.write('      </morph-target>\n')
    
    #-------------------------------------------------------------------------
    #                              w r i t e
    #-------------------------------------------------------------------------
    def write(self, file):
        file.write('   <buffer>\n')

        self.material.write(file)

        self._writeVertices(file)

        self._writeFaces(file)

        if self.bKeyBlocks:
            for i in range(1,len(self.bKeyBlocks)):
                self._writeMorphTarget(file,i)
        
        file.write('   </buffer>\n')
        

