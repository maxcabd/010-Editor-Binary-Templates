//------------------------------------------------
//--- 010 Editor v10.0.2 Binary Template
//
//      File: nucc.h
//   Authors: SutandoTsukai181
//   Version: 1.0
//   Purpose: Contains structs for parsing nuccChunks inside Xfbin files
//  Category: 
// File Mask: 
//  ID Bytes: 
//   History: 
//------------------------------------------------

#include "/../include.h";

typedef struct
{
    u32 PageSize;
    u32 ExtraIndicesSize;
} TNuccPage;

typedef struct
{
    u16 Field00;
    u16 Width;
    u16 Height;
    u16 Field06;

    u32 Size;

    #ifdef NUT
        struct TNut Nut;
    #else
        u8 Data[Size];
    #endif
} TNuccTexture;

typedef struct
{
    u16 GroupCount;
    u16 Field02;
    f32 Field04;
    u32 FloatFormat;

    struct
    {
        if ( FloatFormat & 0x40 ) f32 Bit01Float;
        if ( FloatFormat & 0x20 ) f32 Bit02Float;
        if ( FloatFormat & 0x10 ) f32 Bit03Float[2];
        if ( FloatFormat & 0x04 ) f32 Bit05Float[4];
        if ( FloatFormat & 0x02 ) f32 Bit06Float[4];
        if ( FloatFormat & 0x01 ) f32 Bit07Float[4];
    } Floats;

    local u32 i, j;
    for ( i = 0; i < GroupCount; i++ )
    {
        struct
        {
            s16 TextureCount;
            u16 Field22;
            u32 Field24;
    
            u32 TextureChunkIndices[TextureCount];
    
            if ( exists( Xfbin ) )
            {
                struct
                {
                    FPush();
                    {
                        for ( j = 0; j < TextureCount; j++ )
                        {
                            FSeekRel( startof( Xfbin.ChunkTable.ChunkMaps[GetChunkMapIndex(
                                TextureChunkIndices[j],
                                parentof(parentof(parentof(parentof(this)))).pageStart
                            )] ) );
                            struct TChunkMap ChunkMap;
                        }
                    }
                    FPop();
                } TextureChunks;
            }
        } TextureGroup;
    }
} TNuccMaterial <optimize=false>;