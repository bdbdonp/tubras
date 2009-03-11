// Copyright (C) 2002-2007 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h
#define _IRR_COMPILE_WITH_IRRB_MESH_LOADER_
#ifdef _IRR_COMPILE_WITH_IRRB_MESH_LOADER_
#include "CIrrBMeshWriter.h"
#include "CIrrBMeshFileLoader.h"
#include "os.h"
#include "IXMLReader.h"
#include "SAnimatedMesh.h"
#include "fast_atof.h"
#include "IReadFile.h"
#include "IAttributes.h"
#include "IMeshSceneNode.h"
#include "SMeshBufferLightMap.h"

namespace irr
{
namespace scene
{


//! Constructor
CIrrBMeshFileLoader::CIrrBMeshFileLoader(scene::ISceneManager* smgr, io::IFileSystem* fs)
    : SceneManager(smgr), FileSystem(fs)
{
    Driver = smgr->getVideoDriver();
}


//! destructor
CIrrBMeshFileLoader::~CIrrBMeshFileLoader()
{
}


//! Returns true if the file maybe is able to be loaded by this class.
/** This decision should be based only on the file extension (e.g. ".cob") */
bool CIrrBMeshFileLoader::isALoadableFileExtension(const core::string<c16>& filename) const
{
	return core::hasFileExtension ( filename, "irrbmesh");
}


//! creates/loads an animated mesh from the file.
//! \return Pointer to the created mesh. Returns 0 if loading failed.
//! If you no longer need the mesh, you should call IAnimatedMesh::drop().
//! See IReferenceCounted::drop() for more information.
IAnimatedMesh* CIrrBMeshFileLoader::createMesh(io::IReadFile* file)
{
	IAnimatedMesh* mesh = readMesh(file);

	return mesh;
}


//! reads a mesh section and creates a mesh from it
IAnimatedMesh* CIrrBMeshFileLoader::readMesh(io::IReadFile* reader)
{
    struct irr::scene::IrrbHeader ih;
    u32    sigCheck = MAKE_IRR_ID('i','r','r','b');

    Reader = reader;

    Reader->seek(0);
    if(Reader->read(&ih,sizeof(ih)) != sizeof(ih))
        return 0;

    // sanity checks

    if(ih.hSigCheck != sigCheck)
        return 0;

    if(ih.hMeshCount < 1)
        return 0;

	SAnimatedMesh* animatedmesh = new SAnimatedMesh();
    core::aabbox3df mbb;
    mbb.reset(0.f,0.f,0.f);

    Materials.clear();

    for(u32 i=0; i<ih.hMeshCount; i++)
    {
        SMesh* mesh = _readMesh_1_6(i);
        if(mesh)
        {
            mbb.addInternalBox(mesh->getBoundingBox());
            animatedmesh->addMesh(mesh);
            mesh->drop();
        }
    }

    animatedmesh->setBoundingBox(mbb);

    return animatedmesh;
}

u32 CIrrBMeshFileLoader::readChunk(struct IrrbChunkInfo& chunk)
{
    return Reader->read(&chunk, sizeof(chunk));
}

irr::core::stringc CIrrBMeshFileLoader::readStringChunk()
{
    c8  buf[256];
    irr::core::stringc result="";

    struct IrrbChunkInfo chunk;
    Reader->read(&chunk, sizeof(chunk));
    if(chunk.iId != CID_STRING)
        return result;

    memset(buf,0,sizeof(buf));
    Reader->read(buf, chunk.iSize);
    result = buf;
    return result;

}



SMesh* CIrrBMeshFileLoader::_readMesh_1_6(u32 index)
{

    u32 idx=0;
    struct IrrbChunkInfo ci;
    struct IrrbMeshInfo  mi;


    // position to the correct mesh
    Reader->seek(sizeof(struct IrrbHeader));
    readChunk(ci);

    while(idx < index)
    {
        u32 cpos = Reader->getPos();
        Reader->seek(cpos+ci.iSize);
        readChunk(ci);
        ++idx;
    }

    if(ci.iId != CID_MESH)
        return 0;

    Reader->read(&mi, sizeof(mi));
    if(mi.iMeshBufferCount == 0)
        return 0;

    //
    // read vertex & index data
    //

    u32 vbufsize,ibufsize;
    vbufsize = sizeof(struct IrrbVertex) * mi.iVertexCount;
    ibufsize = sizeof(u16) * mi.iIndexCount;

    VBuffer = (struct IrrbVertex*)malloc(vbufsize);
    IBuffer = (u16 *)malloc(ibufsize);

    Reader->read(VBuffer,vbufsize);
    Reader->read(IBuffer,ibufsize);

    //
    // read & create materials
    //
    u32 matBufSize = sizeof(struct IrrbMaterial_1_6);
    u32 layBufSize = sizeof(struct IrrbMaterialLayer_1_6)*4;
    Material = (struct IrrbMaterial_1_6*) malloc(matBufSize);
    Layer = (struct IrrbMaterialLayer_1_6*) malloc(layBufSize);
    for(u32 i=0; i<mi.iMaterialCount; i++)
    {
        Reader->read(Material,matBufSize);
        irr::video::SMaterial material;
        setMaterial(material,*Material);

        for(u32 j=0; j<Material->mLayerCount; j++)
        {
            irr::core::stringc textureName = readStringChunk();
            Reader->read(Layer,sizeof(struct IrrbMaterialLayer_1_6));
            setMaterialLayer(material, j, textureName, *Layer);
        }

        Materials.push_back(material);
    }
    free(Material);
    free(Layer);

    //
    // read meshbuffer data
    //
    readChunk(ci);
    if(ci.iId != CID_MESHBUF)
    {
        free(VBuffer);
        free(IBuffer);
        return 0;
    }

	SMesh* mesh = new SMesh();
    
    u32 mbiSize = mi.iMeshBufferCount * sizeof(struct IrrbMeshBufInfo_1_6);

    MBuffer = (IrrbMeshBufInfo_1_6*) malloc(mbiSize);
    Reader->read(MBuffer,mbiSize);

    for(idx=0; idx<mi.iMeshBufferCount; idx++)
    {
        IMeshBuffer* buffer = createMeshBuffer(idx);
        if(buffer)
        {
            mesh->addMeshBuffer(buffer);
            buffer->drop();
        }
    }

    free(MBuffer);
    free(VBuffer);
    free(IBuffer);
        

    //
    // todo add bounding box to irrbmesh format...
    // 
    core::aabbox3df mbb(mi.ibbMin.x,mi.ibbMin.y,mi.ibbMin.z,
        mi.ibbMax.x,mi.ibbMax.y,mi.ibbMax.z);
    mesh->setBoundingBox(mbb);

	return mesh;
}

void CIrrBMeshFileLoader::setMaterialLayer(video::SMaterial& material, u8 layerNumber, irr::core::stringc mTexture, struct IrrbMaterialLayer_1_6& layer)
{

    video::IImage* img=0;
    video::ITexture* tex=0;

    if(layerNumber > 3)
        return;

    tex = Driver->findTexture(mTexture);
    if(!tex)
    {
        img = Driver->createImageFromFile(mTexture);
        if(img)
        {
            tex = Driver->addTexture(mTexture,img);
            img->drop();
        }
    }
    if(tex)
    {
        material.TextureLayer[layerNumber].Texture = tex;
        material.TextureLayer[layerNumber].BilinearFilter = layer.mBilinearFilter;
        material.TextureLayer[layerNumber].TrilinearFilter = layer.mTrilinearFilter;
        material.TextureLayer[layerNumber].AnisotropicFilter = layer.mAnisotropicFilter;
        material.TextureLayer[layerNumber].TextureWrap = (irr::video::E_TEXTURE_CLAMP)layer.mTextureWrap;
        irr::core::matrix4 mat4;
        memcpy(mat4.pointer(),&layer.mMatrix,sizeof(u16)*16);
        material.TextureLayer[layerNumber].setTextureMatrix(mat4);
    }

}


void CIrrBMeshFileLoader::setMaterial(video::SMaterial& material, struct IrrbMaterial_1_6& mat)
{    
    material.MaterialType = (irr::video::E_MATERIAL_TYPE)mat.mType;
    material.AmbientColor.color = mat.mAmbient;
    material.DiffuseColor.color= mat.mDiffuse;
    material.EmissiveColor.color = mat.mEmissive;
    material.SpecularColor.color = mat.mSpecular;
    material.Shininess = mat.mShininess;
    material.MaterialTypeParam = mat.mParm1;
    material.MaterialTypeParam2 = mat.mParm2;
    material.Wireframe = mat.mWireframe;
    material.GouraudShading = mat.mGrouraudShading;
    material.Lighting = mat.mLighting;
    material.ZWriteEnable = mat.mZWriteEnabled;
    material.ZBuffer = mat.mZBuffer;
    material.BackfaceCulling = mat.mBackfaceCulling;
    material.FogEnable = mat.mFogEnable;
    material.NormalizeNormals = mat.mNormalizeNormals;
    material.AntiAliasing = mat.mAntiAliasing;
    material.ColorMask = mat.mColorMask;
}


IMeshBuffer* CIrrBMeshFileLoader::createMeshBuffer(u32 idx)
{
    IMeshBuffer             *buffer = 0;
	SMeshBuffer             *sbuffer1 = 0;
	SMeshBufferLightMap     *sbuffer2 = 0;
	SMeshBufferTangents     *sbuffer3 = 0;
    struct IrrbVertex       *pivb;
    u16                     *pindices;

    struct IrrbMeshBufInfo_1_6& mbi=MBuffer[idx];
    pivb = &VBuffer[mbi.iVertStart];
    pindices = &IBuffer[mbi.iIndexStart];


    if(mbi.iVertexType == irr::video::EVT_2TCOORDS)
    {
        sbuffer2 = new SMeshBufferLightMap();
        buffer = sbuffer2;
        sbuffer2->Material = Materials[mbi.iMaterialIndex];
    }
    else if(mbi.iVertexType == irr::video::EVT_TANGENTS)
    {
        sbuffer3 = new SMeshBufferTangents();
        buffer = sbuffer3;
        sbuffer3->Material = Materials[mbi.iMaterialIndex];
    }
    else // EVT_STANDARD
    {
        sbuffer1 = new SMeshBuffer();
        buffer = sbuffer1;
        sbuffer1->Material = Materials[mbi.iMaterialIndex];
    }

    for(idx=0; idx<mbi.iVertCount; idx++)
    {

        video::S3DVertex vtx0;
		video::S3DVertex2TCoords vtx1;
		video::S3DVertexTangents vtx2;

        video::S3DVertex* vtx=0;


        if(mbi.iVertexType == irr::video::EVT_2TCOORDS)
            vtx = &vtx1;
        else if(mbi.iVertexType == irr::video::EVT_TANGENTS)
            vtx = &vtx2;
        else vtx = &vtx0;

        // set common data
        vtx->Pos.X = pivb->vPos.x;
        vtx->Pos.Y = pivb->vPos.y;
        vtx->Pos.Z = pivb->vPos.z;

        vtx->Normal.X = pivb->vNormal.x;
        vtx->Normal.Y = pivb->vNormal.y;
        vtx->Normal.Z = pivb->vNormal.z;

        vtx->Color = pivb->vColor;

        vtx->TCoords.X = pivb->vUV1.x;
        vtx->TCoords.Y = pivb->vUV1.y;

        if(mbi.iVertexType == irr::video::EVT_2TCOORDS)
        {
            vtx1.TCoords2.X = pivb->vUV2.x;
            vtx1.TCoords2.Y = pivb->vUV2.y;
            sbuffer2->Vertices.push_back(vtx1);
        }
        else if(mbi.iVertexType == irr::video::EVT_TANGENTS)
        {
            vtx2.Tangent.X = pivb->vTangent.x;
            vtx2.Tangent.Y = pivb->vTangent.y;
            vtx2.Tangent.Z = pivb->vTangent.z;

            vtx2.Binormal.X = pivb->vBiNormal.x;
            vtx2.Binormal.Y = pivb->vBiNormal.y;
            vtx2.Binormal.Z = pivb->vBiNormal.z;
            sbuffer3->Vertices.push_back(vtx2);
        }
        else
        {
            sbuffer1->Vertices.push_back(vtx0);

        }
        ++pivb;
    }

    for(idx=0; idx<mbi.iIndexCount; idx++)
    {
        if(mbi.iVertexType == irr::video::EVT_2TCOORDS)
            sbuffer2->Indices.push_back(*pindices);
        else if(mbi.iVertexType == irr::video::EVT_TANGENTS)
            sbuffer3->Indices.push_back(*pindices);
        else
            sbuffer1->Indices.push_back(*pindices);
        ++pindices;
    }

    core::aabbox3df mbb(mbi.ibbMin.x,mbi.ibbMin.y,mbi.ibbMin.z,
        mbi.ibbMax.x,mbi.ibbMax.y,mbi.ibbMax.z);
    buffer->setBoundingBox(mbb);

    return buffer;
}

} // end namespace scene
} // end namespace irr

#endif // _IRR_COMPILE_WITH_IRRB_MESH_LOADER_