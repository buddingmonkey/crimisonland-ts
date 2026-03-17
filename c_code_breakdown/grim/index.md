# Grim Engine (grim.dll) Decompiled Code Breakdown

This directory contains the decompiled and renamed grim.dll C code split into logical modules.
The original monolithic file was ~51,360 lines. These files are for reference/search only and are not meant to compile.

## File Index

| File | Lines | Functions | Description |
|------|-------|-----------|-------------|
| `_globals.c` | 58 | — | Global variable declarations, typedefs, struct definitions, and file header |
| `engine_core.c` | 2,759 | 57 | Grim engine core: initialization, shutdown, main loop, config save/load, window creation/destruction, device reset/test, timer tick/update, config dialog, version queries, memory allocator, DLL init/term, atexit registration, CRT buffer helpers, and full engine init. |
| `d3d.c` | 1,591 | 48 | Direct3D backend: D3D device initialization/shutdown, render state setup, vertex buffer create/release, backup/restore textures, render context management, and D3DX SSE feature detection. |
| `input.c` | 1,084 | 39 | Input system: keyboard init/poll/shutdown/key-down/key-press, mouse init/poll/shutdown/button/position/delta, joystick init/poll/shutdown/button/axis/POV/direction, key char buffer, input flush, and key-active checks. |
| `textures.c` | 1,829 | 28 | Texture system: texture load/create/destroy/bind/release/validate, slot finding, name comparison, format selection/support, string table load/lookup, file stream reading, and extension matching. |
| `rendering.c` | 1,263 | 32 | Low-level Grim2D draw primitives: batch flush/begin/end, vertex submission (raw, offset, transform, color variants), quad/rect/circle/line drawing, fullscreen quad/color, color/UV/rotation/sub-rect setters, atlas frame, render target, and clear. These are generic draw-call wrappers used by higher-level game and UI code — no UI logic (menus, buttons, state) lives here. |
| `pixel_formats.c` | 4,250 | 118 | Pixel format system: format constructors for all D3D surface formats, format info lookup/compare/find, pixel read/write row functions, dithered write operations, pixel format conversions (A8R8G8B8 to all targets), color key application per format, and dispatch tables. |
| `mipmaps.c` | 6,157 | 60 | Mipmap generation and DXT compression: box filter (generic, MMX, BGRA, RGB), downsample dispatch, blit 2D/3D, DXT1/2/3/4/5 encode/decode, RGB565 pack/decode, premultiply/unpremultiply RGBA, mipmap create, filter selection, color key application, and CRC32. |
| `image_loaders.c` | 2,870 | 24 | Image loading: format detection, dimension checking, load-from-file/memory dispatch, individual format loaders (BMP, DDS, JPG, PNG, PNM, TGA), BMP header parsing, and surface blitting. |
| `jpeg_decoder.c` | 12,801 | 187 | JPEG decoder: JFIF decompression (create/destroy, header reading, scanline processing, MCU decoding, Huffman decoding, dequantization, color conversion, upsampling, dithering, and error handling). |
| `png_decoder.c` | 5,039 | 102 | PNG decoder: grim PNG wrappers (header/chunk reading, gamma tables, palette, transformations, row processing, state machine) and core libpng functions (CRC, malloc, error, read, create structs). |
| `compression.c` | 6,667 | 76 | Decompression libraries: ZIP archive reader (init/close, header/entry reading, buffer management), zlib inflate (blocks, codes, trees, Huffman build, fast inflate), LZMA decompression, and zlib memory helpers. |
| `sound.c` | 14 | 1 | Sound system: DirectSound initialization and audio device setup. |
| `math.c` | 555 | 22 | 3D math: matrix operations (identity, inverse, multiply, transpose, transform-vec3), quaternion operations (from-axis-angle, from-euler, multiply, slerp), vec2/vec3 normalize/transform, and math dispatch init. |
| `text.c` | 282 | 5 | Text rendering: text width measurement, mono/small text drawing, and formatted text output. |
| `sse_math.c` | 934 | 22 | SIMD/FPU math: SSE and SSE2 function pointer setup, MMX/SSE feature detection, processor feature queries, CPUID checks, D3DX math init, SSE2 availability check, SSE/FPU matrix operations (identity, transpose, multiply, inverse, transform), and FPU control word management. |
| `mesh_loader.c` | 1,335 | 10 | 3D mesh/model loading: mesh data parsing, vertex buffer allocation/freeing, texture processing, mipmap format dispatch and downsampling, skeletal mesh skinning, model loading from ZIP/buffer, mesh converter alloc/destroy, and surface blit operations. |
| `skinning.c` | 584 | 3 | Skeletal mesh skinning: buffer allocation and weight blending (2-weight, 3-weight). |
| `vertex_convert.c` | 131 | 2 | Vertex space conversion: converter destroy, vertex space conversion, and related transform utilities. |
| `unwind_stubs.c` | 1,158 | 84 | Exception unwind stubs: compiler-generated cleanup handlers for structured exception handling and C++ destructors. |

**Total**: 51,361 lines across 20 files
