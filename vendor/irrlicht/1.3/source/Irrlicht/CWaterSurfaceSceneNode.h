// Copyright (C) 2002-2007 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_WATER_SURFACE_SCENE_NODE_H_INCLUDED__
#define __C_WATER_SURFACE_SCENE_NODE_H_INCLUDED__

#include "CMeshSceneNode.h"

namespace irr
{
namespace scene
{

	class CWaterSurfaceSceneNode : public CMeshSceneNode
	{
	public:

		//! constructor
		CWaterSurfaceSceneNode(f32 waveHeight, f32 waveSpeed, f32 waveLength, 
			IMesh* mesh, ISceneNode* parent, ISceneManager* mgr,	s32 id,
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& rotation = core::vector3df(0,0,0),
			const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f));

		//! destructor
		virtual ~CWaterSurfaceSceneNode();

		//! frame
		virtual void OnRegisterSceneNode();

		//! Returns type of the scene node
		virtual ESCENE_NODE_TYPE getType() { return ESNT_WATER_SURFACE; }

		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options);
		virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options);

	private:

		void animateWaterSurface();
		f32 WaveLength;
		f32 WaveSpeed;
		f32 WaveHeight;
		IMesh* OriginalMesh;
	};

} // end namespace scene
} // end namespace irr

#endif

