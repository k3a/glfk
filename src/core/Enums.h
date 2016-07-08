/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#define GLFK_ENUM(name) namespace name { enum E
#define GLFK_ENUM_END ;}

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

