/*

	TVP2 ( T Visual Presenter 2 )  A script authoring tool
	Copyright (C) 2000-2004  W.Dee <dee@kikyou.info>

	See details of license at "license.txt"


*/
/* core C routines for graphics operations */
/* this file is always generated by gengl.pl rev. 0.1 */
#ifndef _TVPGL_H_
#define _TVPGL_H_

/*
	key to blending suffix:
	d : destination has alpha
	a : destination has additive-alpha
	o : blend with opacity
*/


/*[*/
#ifdef __cplusplus
 extern "C" {
#endif
/*]*/

/*[*/
#pragma pack(push, 4)
typedef struct
{
	/* structure used for adjustment of gamma levels */

	float RGamma; /* R gamma   ( 0.10 -- 1.00 -- 9.99) */
	tjs_int RFloor;   /* output floor value  ( 0 -- 255 ) */
	tjs_int RCeil;    /* output ceil value ( 0 -- 255 ) */
	float GGamma; /* G */
	tjs_int GFloor;
	tjs_int GCeil;
	float BGamma; /* B */
	tjs_int BFloor;
	tjs_int BCeil;
} tTVPGLGammaAdjustData;
#pragma pack(pop)
/*]*/

#ifdef _WIN32
#define TVP_GL_FUNC_DECL(rettype, funcname, arg)  rettype __cdecl funcname arg
#define TVP_GL_FUNC_EXTERN_DECL(rettype, funcname, arg)  extern rettype __cdecl funcname arg
#define TVP_GL_FUNC_PTR_DECL(rettype, funcname, arg) rettype __cdecl (*funcname) arg
#define TVP_GL_FUNC_PTR_EXTERN_DECL_(rettype, funcname, arg) extern rettype __cdecl (*funcname) arg
#define TVP_GL_FUNC_PTR_EXTERN_DECL TVP_GL_FUNC_PTR_EXTERN_DECL_
#endif

extern unsigned char TVP252DitherPalette[3][256];

#define TVP_TLG6_H_BLOCK_SIZE 8
#define TVP_TLG6_W_BLOCK_SIZE 8

/* put platform dependent declaration here */

/*[*/
#pragma pack(push, 4)
typedef struct
{
	tjs_uint8 R[256];
	tjs_uint8 G[256];
	tjs_uint8 B[256];
} tTVPGLGammaAdjustTempData;
#pragma pack(pop)
/*]*/
/* begin function list */
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAlphaBlend,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAlphaBlend_HDA,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAlphaBlend_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAlphaBlend_HDA_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAlphaBlend_d,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAlphaBlend_a,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAlphaBlend_do,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAlphaBlend_ao,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAdditiveAlphaBlend,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAdditiveAlphaBlend_HDA,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAdditiveAlphaBlend_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAdditiveAlphaBlend_HDA_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAdditiveAlphaBlend_a,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAdditiveAlphaBlend_ao,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConvertAdditiveAlphaToAlpha,  (tjs_uint32 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConvertAlphaToAdditiveAlpha,  (tjs_uint32 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAlphaBlend,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAlphaBlend_HDA,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAlphaBlend_o,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAlphaBlend_HDA_o,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAlphaBlend_d,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAlphaBlend_a,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAlphaBlend_do,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAlphaBlend_ao,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAdditiveAlphaBlend,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAdditiveAlphaBlend_HDA,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAdditiveAlphaBlend_o,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAdditiveAlphaBlend_HDA_o,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAdditiveAlphaBlend_a,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchAdditiveAlphaBlend_ao,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAlphaBlend,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAlphaBlend_HDA,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAlphaBlend_o,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAlphaBlend_HDA_o,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAlphaBlend_d,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAlphaBlend_a,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAlphaBlend_do,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAlphaBlend_ao,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAdditiveAlphaBlend,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAdditiveAlphaBlend_HDA,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAdditiveAlphaBlend_o,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAdditiveAlphaBlend_HDA_o,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAdditiveAlphaBlend_a,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransAdditiveAlphaBlend_ao,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPCopyOpaqueImage,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConstAlphaBlend,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConstAlphaBlend_HDA,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConstAlphaBlend_d,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConstAlphaBlend_a,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchCopyOpaqueImage,  (tjs_uint32 *dest, tjs_int destlen, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchConstAlphaBlend,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPInterpStretchConstAlphaBlend,  (tjs_uint32 *dest, tjs_int destlen, const tjs_uint32 *src1, const tjs_uint32 *src2, tjs_int blend_y, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchConstAlphaBlend_HDA,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchConstAlphaBlend_d,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchConstAlphaBlend_a,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransCopyOpaqueImage,  (tjs_uint32 *dest, tjs_int destlen, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransConstAlphaBlend,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransConstAlphaBlend_HDA,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransConstAlphaBlend_d,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransConstAlphaBlend_a,  (tjs_uint32 *dest, tjs_int len, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConstAlphaBlend_SD,  (tjs_uint32 *dest, const tjs_uint32 *src1, const tjs_uint32 *src2, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConstAlphaBlend_SD_a,  (tjs_uint32 *dest, const tjs_uint32 *src1, const tjs_uint32 *src2, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConstAlphaBlend_SD_d,  (tjs_uint32 *dest, const tjs_uint32 *src1, const tjs_uint32 *src2, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPInitUnivTransBlendTable,  (tjs_uint32 *table, tjs_int phase, tjs_int vague));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPInitUnivTransBlendTable_d,  (tjs_uint32 *table, tjs_int phase, tjs_int vague));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPInitUnivTransBlendTable_a,  (tjs_uint32 *table, tjs_int phase, tjs_int vague));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPUnivTransBlend,  (tjs_uint32 *dest, const tjs_uint32 *src1, const tjs_uint32 *src2, const tjs_uint8 *rule, const tjs_uint32 *table, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPUnivTransBlend_switch,  (tjs_uint32 *dest, const tjs_uint32 *src1, const tjs_uint32 *src2, const tjs_uint8 *rule, const tjs_uint32 *table, tjs_int len, tjs_int src1lv, tjs_int src2lv));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPUnivTransBlend_d,  (tjs_uint32 *dest, const tjs_uint32 *src1, const tjs_uint32 *src2, const tjs_uint8 *rule, const tjs_uint32 *table, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPUnivTransBlend_switch_d,  (tjs_uint32 *dest, const tjs_uint32 *src1, const tjs_uint32 *src2, const tjs_uint8 *rule, const tjs_uint32 *table, tjs_int len, tjs_int src1lv, tjs_int src2lv));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPUnivTransBlend_a,  (tjs_uint32 *dest, const tjs_uint32 *src1, const tjs_uint32 *src2, const tjs_uint8 *rule, const tjs_uint32 *table, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPUnivTransBlend_switch_a,  (tjs_uint32 *dest, const tjs_uint32 *src1, const tjs_uint32 *src2, const tjs_uint8 *rule, const tjs_uint32 *table, tjs_int len, tjs_int src1lv, tjs_int src2lv));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap_o,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap65,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap65_o,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap_HDA,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap_HDA_o,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap65_HDA,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap65_HDA_o,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap_d,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap65_d,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap_a,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap65_a,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap_do,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap65_do,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap_ao,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPApplyColorMap65_ao,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_uint32 color, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConstColorAlphaBlend,  (tjs_uint32 *dest, tjs_int len, tjs_uint32 color, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConstColorAlphaBlend_d,  (tjs_uint32 *dest, tjs_int len, tjs_uint32 color, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConstColorAlphaBlend_a,  (tjs_uint32 *dest, tjs_int len, tjs_uint32 color, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPRemoveConstOpacity,  (tjs_uint32 *dest, tjs_int len, tjs_int strength));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPRemoveOpacity,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPRemoveOpacity_o,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_int strength));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPRemoveOpacity65,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPRemoveOpacity65_o,  (tjs_uint32 *dest, const tjs_uint8 *src, tjs_int len, tjs_int strength));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAddBlend,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAddBlend_HDA,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAddBlend_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAddBlend_HDA_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPSubBlend,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPSubBlend_HDA,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPSubBlend_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPSubBlend_HDA_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPMulBlend,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPMulBlend_HDA,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPMulBlend_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPMulBlend_HDA_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPColorDodgeBlend,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPColorDodgeBlend_HDA,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPColorDodgeBlend_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPColorDodgeBlend_HDA_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPDarkenBlend,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPDarkenBlend_HDA,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPDarkenBlend_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPDarkenBlend_HDA_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLightenBlend,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLightenBlend_HDA,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLightenBlend_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLightenBlend_HDA_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPScreenBlend,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPScreenBlend_HDA,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPScreenBlend_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPScreenBlend_HDA_o,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len, tjs_int opa));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchCopy,  (tjs_uint32 *dest, tjs_int destlen, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep));
TVP_GL_FUNC_DECL(void, TVPInterpStretchCopy, (tjs_uint32 *dest, tjs_int destlen, const tjs_uint32 *src1, const tjs_uint32 *src2, tjs_int blend_y, tjs_int srcstart, tjs_int srcstep));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPFastLinearInterpH2F,  (tjs_uint32 *dest, tjs_int destlen, const tjs_uint32 *src));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPFastLinearInterpH2B,  (tjs_uint32 *dest, tjs_int destlen, const tjs_uint32 *src));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPFastLinearInterpV2,  (tjs_uint32 *dest, tjs_int destlen, const tjs_uint32 *src0, const tjs_uint32 *src1));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPStretchColorCopy,  (tjs_uint32 *dest, tjs_int destlen, const tjs_uint32 *src, tjs_int srcstart, tjs_int srcstep));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransCopy,  (tjs_uint32 *dest, tjs_int destlen, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPLinTransColorCopy,  (tjs_uint32 *dest, tjs_int destlen, const tjs_uint32 *src, tjs_int sx, tjs_int sy, tjs_int stepx, tjs_int stepy, tjs_int srcpitch));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPMakeAlphaFromKey,  (tjs_uint32 *dest, tjs_int len, tjs_uint32 key));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPCopyMask,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPCopyColor,  (tjs_uint32 *dest, const tjs_uint32 *src, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBindMaskToMain,  (tjs_uint32 *main, const tjs_uint8 *mask, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPFillARGB,  (tjs_uint32 *dest, tjs_int len, tjs_uint32 value));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPFillARGB_NC,  (tjs_uint32 *dest, tjs_int len, tjs_uint32 value));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPFillColor,  (tjs_uint32 *dest, tjs_int len, tjs_uint32 color));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPFillMask,  (tjs_uint32 *dest, tjs_int len, tjs_uint32 mask));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPSwapLine8,  (tjs_uint8 *line1, tjs_uint8 *line2, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPSwapLine32,  (tjs_uint32 *line1, tjs_uint32 *line2, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPReverse8,  (tjs_uint8 *pixels, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPReverse32,  (tjs_uint32 *pixels, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPDoGrayScale,  (tjs_uint32 *dest, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPInitGammaAdjustTempData,  (tTVPGLGammaAdjustTempData *temp, const tTVPGLGammaAdjustData *data));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPUninitGammaAdjustTempData,  (tTVPGLGammaAdjustTempData *temp));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPAdjustGamma,  (tjs_uint32 *dest, tjs_int len, tTVPGLGammaAdjustTempData *temp));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPChBlurMulCopy65,  (tjs_uint8 *dest, const tjs_uint8 *src, tjs_int len, tjs_int level));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPChBlurAddMulCopy65,  (tjs_uint8 *dest, const tjs_uint8 *src, tjs_int len, tjs_int level));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPChBlurCopy65,  (tjs_uint8 *dest, tjs_int destpitch, tjs_int destwidth, tjs_int destheight, const tjs_uint8 * src, tjs_int srcpitch, tjs_int srcwidth, tjs_int srcheight, tjs_int blurwidth, tjs_int blurlevel));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLExpand1BitTo8BitPal,  (tjs_uint8 *dest, const tjs_uint8 *buf, tjs_int len, const tjs_uint32 *pal));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLExpand1BitTo32BitPal,  (tjs_uint32 *dest, const tjs_uint8 *buf, tjs_int len, const tjs_uint32 *pal));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLExpand4BitTo8BitPal,  (tjs_uint8 *dest, const tjs_uint8 *buf, tjs_int len, const tjs_uint32 *pal));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLExpand4BitTo32BitPal,  (tjs_uint32 *dest, const tjs_uint8 *buf, tjs_int len, const tjs_uint32 *pal));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLExpand8BitTo8BitPal,  (tjs_uint8 *dest, const tjs_uint8 *buf, tjs_int len, const tjs_uint32 *pal));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLExpand8BitTo32BitPal,  (tjs_uint32 *dest, const tjs_uint8 *buf, tjs_int len, const tjs_uint32 *pal));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPExpand8BitTo32BitGray,  (tjs_uint32 *dest, const tjs_uint8 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLConvert15BitTo8Bit,  (tjs_uint8 *dest, const tjs_uint16 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLConvert15BitTo32Bit,  (tjs_uint32 *dest, const tjs_uint16 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLConvert24BitTo8Bit,  (tjs_uint8 *dest, const tjs_uint8 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLConvert24BitTo32Bit,  (tjs_uint32 *dest, const tjs_uint8 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPConvert24BitTo32Bit,  (tjs_uint32 *dest, const tjs_uint8 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLConvert32BitTo8Bit,  (tjs_uint8 *dest, const tjs_uint32 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLConvert32BitTo32Bit_NoneAlpha,  (tjs_uint32 *dest, const tjs_uint32 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLConvert32BitTo32Bit_MulAddAlpha,  (tjs_uint32 *dest, const tjs_uint32 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPBLConvert32BitTo32Bit_AddAlpha,  (tjs_uint32 *dest, const tjs_uint32 *buf, tjs_int len));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPDither32BitTo16Bit565,  (tjs_uint16 *dest, const tjs_uint32 *src, tjs_int len, tjs_int xofs, tjs_int yofs));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPDither32BitTo16Bit555,  (tjs_uint16 *dest, const tjs_uint32 *src, tjs_int len, tjs_int xofs, tjs_int yofs));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPDither32BitTo8Bit,  (tjs_uint8 *dest, const tjs_uint32 *src, tjs_int len, tjs_int xofs, tjs_int yofs));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPTLG5ComposeColors3To4,  (tjs_uint8 *outp, const tjs_uint8 *upper, tjs_uint8 * const * buf, tjs_int width));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPTLG5ComposeColors4To4,  (tjs_uint8 *outp, const tjs_uint8 *upper, tjs_uint8 * const* buf, tjs_int width));
TVP_GL_FUNC_PTR_EXTERN_DECL(tjs_int, TVPTLG5DecompressSlide,  (tjs_uint8 *out, const tjs_uint8 *in, tjs_int insize, tjs_uint8 *text, tjs_int initialr));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPTLG6DecodeGolombValuesForFirst,  (tjs_int8 *pixelbuf, tjs_int pixel_count, tjs_uint8 *bit_pool));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPTLG6DecodeGolombValues,  (tjs_int8 *pixelbuf, tjs_int pixel_count, tjs_uint8 *bit_pool));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPTLG6DecodeLineGeneric,  (tjs_uint32 *prevline, tjs_uint32 *curline, tjs_int width, tjs_int start_block, tjs_int block_limit, tjs_uint8 *filtertypes, tjs_int skipblockbytes, tjs_uint32 *in, tjs_uint32 initialp, tjs_int oddskip, tjs_int dir));
TVP_GL_FUNC_PTR_EXTERN_DECL(void, TVPTLG6DecodeLine,  (tjs_uint32 *prevline, tjs_uint32 *curline, tjs_int width, tjs_int block_count, tjs_uint8 *filtertypes, tjs_int skipblockbytes, tjs_uint32 *in, tjs_uint32 initialp, tjs_int oddskip, tjs_int dir));
/* end function list */

TVP_GL_FUNC_EXTERN_DECL(void, TVPInitTVPGL, ());
TVP_GL_FUNC_EXTERN_DECL(void, TVPUninitTVPGL, ());
/*[*/
#ifdef __cplusplus
 }
#endif
/*]*/
/* some utilities */
/*[*/
#define TVP_RGB2COLOR(r,g,b) ((((r)<<16) + ((g)<<8) + (b)) | 0xff000000)
#define TVP_RGBA2COLOR(r,g,b,a) \
	(((a)<<24) +  (((r)<<16) + ((g)<<8) + (b)))
/*]*/

#endif
/* end of the file */
