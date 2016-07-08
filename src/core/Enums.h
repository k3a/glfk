/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#define GLFK_ENUM(name) namespace name { enum E
#define GLFK_ENUM_END ;};

GLFK_ENUM(CubeFace) {
    POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
}GLFK_ENUM_END;

GLFK_ENUM(BufferUsage) {
    STREAM_DRAW = GL_STREAM_DRAW,
    STREAM_READ = GL_STREAM_READ,
    STREAM_COPY = GL_STREAM_COPY,
    STATIC_DRAW = GL_STATIC_DRAW,
    STATIC_READ = GL_STATIC_READ,
    STATIC_COPY = GL_STATIC_COPY,
    DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    DYNAMIC_READ = GL_DYNAMIC_READ,
    DYNAMIC_COPY = GL_DYNAMIC_COPY
}GLFK_ENUM_END;

GLFK_ENUM(AttribType) {
    BYTE = GL_BYTE,
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    SHORT = GL_SHORT,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    INT = GL_INT,
    UNSIGNED_INT = GL_UNSIGNED_INT,
    HALF_FLOAT = GL_HALF_FLOAT,
    FLOAT = GL_FLOAT,
    DOUBLE = GL_DOUBLE,
    FIXED = GL_FIXED,
    INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
    UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
    UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV
}GLFK_ENUM_END;

GLFK_ENUM(FramebufferStatus) {
    /// framebuffer is complete
    FRAMEBUFFER_COMPLETE = GL_FRAMEBUFFER_COMPLETE,
    /// framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist
    FRAMEBUFFER_UNDEFINED = GL_FRAMEBUFFER_UNDEFINED,
    /// any of the framebuffer attachment points are framebuffer incomplete
    FRAMEBUFFER_INCOMPLETE_ATTACHMENT = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
    /// framebuffer does not have at least one image attached to it
    FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
    /// the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi
    FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
    /// GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER
    FRAMEBUFFER_INCOMPLETE_READ_BUFFER = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
    /// combination of internal formats of the attached images violates an implementation-dependent set of restrictions
    FRAMEBUFFER_UNSUPPORTED = GL_FRAMEBUFFER_UNSUPPORTED,
    /// value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the
    /// not same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of
    /// GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES
    FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
    /// value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images
    /// are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures.
    FRAMEBUFFER_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
    /// any framebuffer attachment is layered, and any populated attachment is not layered, or if all
    /// populated color attachments are not from textures of the same target.
    FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
}GLFK_ENUM_END;

GLFK_ENUM(DrawMode) {
    POINTS = GL_POINTS,
    LINE_STRIP = GL_LINE_STRIP,
    LINE_LOOP = GL_LINE_LOOP,
    LINES = GL_LINES,
    LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
    LINES_ADJACENCY = GL_LINES_ADJACENCY,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    TRIANGLE_FAN = GL_TRIANGLE_FAN,
    TRIANGLES = GL_TRIANGLES,
    TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
    TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
    PATCHES = GL_PATCHES
}GLFK_ENUM_END;

GLFK_ENUM(IndicesType) {
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    UNSIGNED_INT = GL_UNSIGNED_INT
}GLFK_ENUM_END;

GLFK_ENUM(WrapMode) {
    CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
    REPEAT = GL_REPEAT
}GLFK_ENUM_END;

GLFK_ENUM(MinFilterMode) {
    /// Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates.
    NEAREST = GL_NEAREST,
    /// Returns the weighted average of the four texture elements that are closest to the specified texture coordinates.
    LINEAR = GL_LINEAR,
    /// Chooses the mipmap that most closely matches the size of the pixel being textured and uses the GL_NEAREST criterion
    NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
    /// Chooses the mipmap that most closely matches the size of the pixel being textured and uses the GL_LINEAR criterion
    LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
    /// Chooses the two mipmaps that most closely match the size of the pixel being textured and uses the GL_NEAREST criterion
    NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
    /// Chooses the two mipmaps that most closely match the size of the pixel being textured and uses the GL_LINEAR criterion
    LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
}GLFK_ENUM_END;

GLFK_ENUM(MagFilterMode) {
    /// Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates.
    NEAREST = GL_NEAREST,
    /// Returns the weighted average of the texture elements that are closest to the specified texture coordinates.
    LINEAR = GL_LINEAR
}GLFK_ENUM_END;

GLFK_ENUM(InternalFormat) {
    // base internal format ----------------------
    
    /// Depth (D)
    DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
    /// Depth + Stencil (D, S)
    DEPTH_STENCIL = GL_DEPTH_STENCIL,
    /// Red - one channel (R)
    RED = GL_RED,
    /// Red, Green - two channels (R, G)
    RG = GL_RG,
    /// Red, Green, Blue - three channels (R, G, B)
    RGB = GL_RGB,
    // Red, Green, Blue, Alpha - four channels (R, G, B, A)
    RGBA = GL_RGBA,
    
    // sized internal format ------------------------
    
    R8 = GL_R8,
    R8_SNORM = GL_R8_SNORM,
    R16 = GL_R16,
    R16_SNORM = GL_R16_SNORM,
    RG8 = GL_RG8,
    RG8_SNORM = GL_RG8_SNORM,
    RG16 = GL_RG16,
    RG16_SNORM = GL_RG16_SNORM,
    R3_G3_B2 = GL_R3_G3_B2,
    RGB4 = GL_RGB4,
    RGB5 = GL_RGB5,
    RGB8 = GL_RGB8,
    RGB8_SNORM = GL_RGB8_SNORM,
    RGB10 = GL_RGB10,
    RGB12 = GL_RGB12,
    RGB16_SNORM = GL_RGB16_SNORM,
    RGBA2 = GL_RGBA2,
    RGBA4 = GL_RGBA4,
    RGB5_A1 = GL_RGB5_A1,
    RGBA8 = GL_RGBA8,
    RGBA8_SNORM = GL_RGBA8_SNORM,
    RGB10_A2 = GL_RGB10_A2,
    RGB10_A2UI = GL_RGB10_A2UI,
    RGBA12 = GL_RGBA12,
    RGBA16 = GL_RGBA16,
    SRGB8 = GL_SRGB8,
    SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
    R16F = GL_R16F,
    RG16F = GL_RG16F,
    RGB16F = GL_RGB16F,
    RGBA16F = GL_RGBA16F,
    R32F = GL_R32F,
    RG32F = GL_RG32F,
    RGB32F = GL_RGB32F,
    RGBA32F = GL_RGBA32F,
    R11F_G11F_B10F = GL_R11F_G11F_B10F,
    RGB9_E5 = GL_RGB9_E5,
    R8I = GL_R8I,
    R8UI = GL_R8UI,
    R16I = GL_R16I,
    R16UI = GL_R16UI,
    R32I = GL_R32I,
    R32UI = GL_R32UI,
    RG8I = GL_RG8I,
    RG8UI = GL_RG8UI,
    RG16I = GL_RG16I,
    RG16UI = GL_RG16UI,
    RG32I = GL_RG32I,
    RG32UI = GL_RG32UI,
    RGB8I = GL_RGB8I,
    RGB8UI = GL_RGB8UI,
    RGB16I = GL_RGB16I,
    RGB16UI = GL_RGB16UI,
    RGB32I = GL_RGB32I,
    RGB32UI = GL_RGB32UI,
    RGBA8I = GL_RGBA8I,
    RGBA8UI = GL_RGBA8UI,
    RGBA16I = GL_RGBA16I,
    RGBA16UI = GL_RGBA16UI,
    RGBA32I = GL_RGBA32I,
    RGBA32UI = GL_RGBA32UI,
    
    // compressed internal format ---------------------
    
    COMPRESSED_RED = GL_COMPRESSED_RED,
    COMPRESSED_RG = GL_COMPRESSED_RG,
    COMPRESSED_RGB = GL_COMPRESSED_RGB,
    COMPRESSED_RGBA = GL_COMPRESSED_RGBA,
    COMPRESSED_SRGB = GL_COMPRESSED_SRGB,
    COMPRESSED_SRGB_ALPHA = GL_COMPRESSED_SRGB_ALPHA,
    COMPRESSED_RED_RGTC1 = GL_COMPRESSED_RED_RGTC1,
    COMPRESSED_SIGNED_RED_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1,
    COMPRESSED_RG_RGTC2 = GL_COMPRESSED_RG_RGTC2,
    COMPRESSED_SIGNED_RG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2,
#ifdef GL_COMPRESSED_RGBA_BPTC_UNORM
    COMPRESSED_RGBA_BPTC_UNORM = GL_COMPRESSED_RGBA_BPTC_UNORM,
#endif
#ifdef GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM
    COMPRESSED_SRGB_ALPHA_BPTC_UNORM = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
#endif
#ifdef GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT
    COMPRESSED_RGB_BPTC_SIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
#endif
#ifdef GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT
    COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,
#endif
    
}GLFK_ENUM_END;

GLFK_ENUM(PixelCopyDataFormat) {
    STENCIL_INDEX = GL_STENCIL_INDEX,
    DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
    DEPTH_STENCIL = GL_DEPTH_STENCIL,
    RED = GL_RED,
    GREEN = GL_GREEN,
    BLUE = GL_BLUE,
    RGB = GL_RGB,
    BGR = GL_BGR,
    RGBA = GL_RGBA,
    BGRA = GL_BGRA,
}GLFK_ENUM_END;

GLFK_ENUM(PixelDataFormat) {
    RED = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    BGR = GL_BGR,
    RGBA = GL_RGBA,
    BGRA = GL_BGRA,
    RED_INTEGER = GL_RED_INTEGER,
    RG_INTEGER = GL_RG_INTEGER,
    RGB_INTEGER = GL_RGB_INTEGER,
    BGR_INTEGER = GL_BGR_INTEGER,
    RGBA_INTEGER = GL_RGBA_INTEGER,
    BGRA_INTEGER = GL_BGRA_INTEGER,
    STENCIL_INDEX = GL_STENCIL_INDEX,
    DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
    DEPTH_STENCIL = GL_DEPTH_STENCIL,
}GLFK_ENUM_END;

GLFK_ENUM(PixelDataType) {
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    BYTE = GL_BYTE,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    SHORT = GL_SHORT,
    UNSIGNED_INT = GL_UNSIGNED_INT,
    INT = GL_INT,
    FLOAT = GL_FLOAT,
    UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
    UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
    UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
    UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
    UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
    UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
    UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
    UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
    UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
    UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
    UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
    UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
}GLFK_ENUM_END;

GLFK_ENUM(ShaderAttribType) {
    FLOAT = GL_FLOAT,
    VEC2 = GL_FLOAT_VEC2,
    VEC3 = GL_FLOAT_VEC3,
    VEC4 = GL_FLOAT_VEC4,
    MAT2 = GL_FLOAT_MAT2,
    MAT3 = GL_FLOAT_MAT3,
    MAT4 = GL_FLOAT_MAT4,
}GLFK_ENUM_END;

GLFK_ENUM(ShaderUniformType) {
    FLOAT = GL_FLOAT,
    FLOAT_VEC2 = GL_FLOAT_VEC2,
    FLOAT_VEC3 = GL_FLOAT_VEC3,
    FLOAT_VEC4 = GL_FLOAT_VEC4,
    INT = GL_INT,
    INT_VEC2 = GL_INT_VEC2,
    INT_VEC3 = GL_INT_VEC3,
    INT_VEC4 = GL_INT_VEC4,
    BOOL = GL_BOOL,
    BOOL_VEC2 = GL_BOOL_VEC2,
    BOOL_VEC3 = GL_BOOL_VEC3,
    BOOL_VEC4 = GL_BOOL_VEC4,
    FLOAT_MAT2 = GL_FLOAT_MAT2,
    FLOAT_MAT3 = GL_FLOAT_MAT3,
    FLOAT_MAT4 = GL_FLOAT_MAT4,
    SAMPLER_2D = GL_SAMPLER_2D,
    SAMPLER_CUBE = GL_SAMPLER_CUBE
}GLFK_ENUM_END;


